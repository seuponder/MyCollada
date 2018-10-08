#include "CSkeletonData.h"
#include "ColladaDefine.h"
#include "ColladaUtil.h"

NS_C_DRAW_BEGIN

/*
* CBone begin
*/

CBone::~CBone(){
	SAFE_DELETE(m_JointMatrix);
	SAFE_DELETE(m_InverseBindMatrix);
	SAFE_DELETE(m_WorldMatrix);
	SAFE_DELETE(m_SkinningMatrix);
	
	delete_vector_ptr_member(m_Keyframes);
}

CBone::CBone(void){
	m_JointMatrix = new	CMatrix4f();
	// m_InverseBindMatrix = new	CMatrix4f();
	m_WorldMatrix = new	CMatrix4f();
	m_SkinningMatrix = new	CMatrix4f();

}

void CBone::initWithElement(daeElementRef controller, daeElement* bone_root, daeDocument* doc, int p_id, CSkeletonData& skeleton){
	m_ID = get_bone_id(bone_root->getAttribute("id"));
	m_ParentID = p_id;

	// world matrix
	// assign_dom_float4(*m_WorldMatrix, bone_root->getChild("matrix")->getCharData());

	// inverseBindMatrix
	if(!strcmp(bone_root->getAttribute("type"), "JOINT")){
		if(m_InverseBindMatrix == nullptr){
			m_InverseBindMatrix = new	CMatrix4f();
		}
		auto mat =  skeleton.getInvMat(bone_root->getAttribute("sid"));
		assign_dom_float4(*m_InverseBindMatrix, mat);
	}
	else{
		SAFE_DELETE(m_InverseBindMatrix);
	}

	// JointMatrix
	assign_dom_float4(*m_JointMatrix, bone_root->getChild("matrix")->getCharData());

	// skinningmatrix
	// calculate mat

	// key frames
	// todo load key frame

	// add self to CSkeletonData 中
	skeleton.addBone(this);

	// children
	auto chidren = bone_root->getChildren();
	m_ChildCount = 0;
	for(auto child: children){
		if(!strcmp(child->getName(), "node")){
			auto c_ptr = new CBone();
			c_ptr->initWithElement(controller, child, doc,	m_ID, skeleton);

			m_Children.push_back(c_ptr->getID());
		}
	}

}


bool CBone::isBindValid(){
	return m_InverseBindMatrix != nullptr
}


/********************************
* SkeletonData
*********************************/
CSkeletonData::~CSkeletonData()
{
	SAFE_DELETE(m_RootBone);
	SAFE_DELETE(m_BindShapeMatrix);

	deleteInvMatMap();

	// 释放所有的Bone
	delete_vector_ptr_member(m_Bones);

}

/*
* 释放掉inv mat
*/
inline void CSkeletonData::deleteInvMatMap(){
	if(m_InvMatMap != nullptr){
		for(auto entry: m_InverseBindMatrix){
			auto val = entry.getValue();
			SAFE_DELETE_ARR(val);		// 直接用的宏来完成的，直接用getValue 估计是过不去的
			entry.setValue(nullptr);
		}
	}
	m_InvMatMap.clear();
}

/*
* 通过字符串获取对应的 inv mat
*/
float* CSkeletonData::getInvMat(std::string sid){
	return m_InvMatMap.get(sid);
}

/*
*  初始化CSkeletonData
*/
void CSkeletonData::initWithElement(daeElementRef controller, daeElement* bone_root, daeDocument* doc){
	auto dae = doc->getDAE();

	SAFE_DELETE(m_Bones);
	SAFE_DELETER(m_RootBone);
	SAFE_DELETE(m_BindShapeMatrix);

	// bind shape matrix
	auto ele_bsm = controller->getDescendant("bind_shape_matrix");
	assign_dom_float4(m_BindShapeMatrix, ele_bsm->getCharData());

	// 加载骨骼数据
	loadJointInvMats(controller, doc);

	m_RootBone = new CBone();
	m_RootBone.initWithElement(controller, bone_root, doc, 0, joints_inv_mat_map);

}

void CSKeletonData::loadJointInvMats(daeElementRef controller, daeDocument* doc){
	deleteInvMatMap();
	auto dae = doc->getDAE();

	auto ele_joints = controller->getDescendant("joints");
	auto input_vec = vw->getChildrenByType<domInputLocal>();
	size_t inv_stride = 0;
	size_t joint_num = 0;
	std::string name_str;
	std::string mat_str;

	for(auto input: input_vec){
		if(!strcmp(input->getSemantic(), "JOINT")){
			daeElement* joints_src = dae->getDatabase()->idLookup(input->getAttribute("source"), doc);
			auto dom = joints_src->getChildrenByType<domName_array>()[0];		// smartref
			name_str = dom->getCharData();
			joint_num = std::stoi(input->getAttribute("count"));
		}
		
		if(!strcmp(input->getSemantic(), "INV_BIND_MATRIX")){
			daeElement* mats_src = dae->getDatabase()->idLookup(input->getAttribute("source"), doc);
			auto dom = mats_src->getChildrenByType<domFloat_array>()[0];		// smartref
			mat_str = dom->getCharData();

			inv_stride = std::stoi(input->getAttribute("stride"));
		}
	}

	if(!name_str.empty() && !mat_str.empty()){
		// 数组
		std::vector<std::string> vec_str_mat;
		boost::split(vec_str_mat, mat_str, boost::is_any_of(" "), boost::token_compress_on);

		// 数组
		std::vector<std::string> vec_str_name;
		boost::split(vec_str_name, name_str, boost::is_any_of(" "), boost::token_compress_on);

		for(size_t i=0; i < joint_num; i++){
			CMatrix4f* mat = new CMatrix4f();
			for(size_t val_idx=0; val_idx < inv_stride; val_idx ++){
				*mat[val_idx] = std::stof(vec_str_mat[i * inv_stride + val_idx]);
			}
			m_InvMatMap[vec_str_name[i]] = mat;
		}
	}
}


/*
* 获取骨骼的数量
* 需要注意的这个实现是区分了JOINT和普通NODE的，
*/
size_t CSkeletonData::getNoOfBones(){
	return m_Bones.size();
}


/*
* 添加骨骼
*/
bool CSkeletonData::addBone(CBone* bone_ptr){
	if(!m_Bones.find(bone_ptr)){
		m_Bones.push_back(bone_ptr);
		return true;
	}
	return false;
}


NS_C_DRAW_END