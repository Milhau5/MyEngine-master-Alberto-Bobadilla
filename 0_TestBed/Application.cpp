#include "ApplicationClass.h"
void ApplicationClass::InitUserAppVariables()
{
	m_pCamera->SetPosition(vector3(0.0f,3.5f,11.5f));
	
	if(m_nPads == 1)
	{
		m_pMeshMngr->LoadModelUnthreaded("Minecraft\\MC_Steve.obj", "Steve", glm::translate(MEAXISX * 0.0f));
		m_pMeshMngr->LoadModelUnthreaded("Minecraft\\MC_Creeper.obj", "Creeper", glm::translate(MEAXISX *-2.0f));
		m_pMeshMngr->LoadModelUnthreaded("Minecraft\\MC_Creeper.obj", "Creeper", glm::translate(MEAXISX * 2.0f));
	}
	else
	{
		m_m4ObjectTranslation[0] = glm::translate(MEAXISX *-1.0f);
		m_m4ObjectTranslation[1] = glm::translate(MEAXISX * 1.0f);
		m_pMeshMngr->LoadModelUnthreaded("Minecraft\\MC_Steve.obj", "Steve");
		m_pMeshMngr->LoadModelUnthreaded("Minecraft\\MC_Creeper.obj", "Creeper");
		m_pMeshMngr->LoadModelUnthreaded("Minecraft\\MC_Creeper.obj", "Creeper");
	}
		
	m_sSelectedObject = "Steve";
}

void ApplicationClass::UpdateBox(void)
{
	int nInstances = m_pMeshMngr->GetNumberOfInstances();
	m_fBoxSize = 0;
	vector3 v3Size;
	vector3 v3Max;
	vector3 v3Min;
	if(nInstances > 0)
	{
		BoundingObjectClass* pObject = m_pMeshMngr->GetBoundingObject(0);
		v3Max = pObject->GetAABBMax();
		v3Min = pObject->GetAABBMin();
	}
	for (int nInstance = 1; nInstance < nInstances; nInstance++)
	{
		//Get the information of the Bounding Box
		BoundingObjectClass* pObject = m_pMeshMngr->GetBoundingObject(nInstance);
		vector3 v3MaxI = pObject->GetAABBMax();
		vector3 v3MinI = pObject->GetAABBMin();
		if(v3Max.x < v3MaxI.x)
			v3Max.x = v3MaxI.x;
		else if(v3Min.x > v3MinI.x)
			v3Min.x = v3MinI.x;

		if(v3Max.y < v3MaxI.y)
			v3Max.y = v3MaxI.y;
		else if(v3Min.y > v3MinI.y)
			v3Min.y = v3MinI.y;

		if(v3Max.z < v3MaxI.z)
			v3Max.z = v3MaxI.z;
		else if(v3Min.z > v3MinI.z)
			v3Min.z = v3MinI.z;
	}
	float fX = glm::distance(vector3(v3Min.x, 0.0f, 0.0f), vector3(v3Max.x, 0.0f, 0.0f));
	float fY = glm::distance(vector3(0.0f, v3Min.y, 0.0f), vector3(0.0f, v3Max.y, 0.0f));
	float fZ = glm::distance(vector3(0.0f, 0.0f, v3Min.z), vector3(0.0f, 0.0f, v3Max.z));

	m_fBoxSize = fX;
	if(m_fBoxSize < fY)
		m_fBoxSize = fY;
	if(m_fBoxSize < fZ)
		m_fBoxSize = fZ;

	m_v3BoxCentroid = (v3Max + v3Min) / 2.0f;
}
void ApplicationClass::Update (void)
{
	UpdateBox();
	m_pSystem->UpdateTime(); //Update the system
	for (int nPad = 0; nPad < m_nPads; nPad++)
	{
		m_pMeshMngr->SetModelMatrix(m_m4ObjectTranslation[nPad] * m_m4ObjectOrientation[nPad], nPad); //Setting up the Model Matrix
	}
	m_pMeshMngr->Update(); //Update the mesh information

	m_pMeshMngr->SetShaderProgramByName("ALL", "Original");
	std::vector<vector4> lCollisionList = m_pMeshMngr->GetCollisionList();
	for(uint n = 0; n < lCollisionList.size(); n++)
	{
		m_pMeshMngr->SetShaderProgramByNumber(lCollisionList[n].x, lCollisionList[n].y, "Inverse");
	}

	m_pMeshMngr->AddAxisToQueue(glm::translate(m_v3BoxCentroid));
	m_pMeshMngr->AddCubeToQueue(glm::translate(m_v3BoxCentroid)* glm::scale(vector3(m_fBoxSize, m_fBoxSize,m_fBoxSize)), MERED, WIRE);

	//First person camera movement
	if(m_bFPC == true)
		CameraRotation();

	if(m_bArcBall == true)
	{
		ArcBall();
		m_pMeshMngr->SetModelMatrix(m_m4ObjectTranslation[0] * m_m4ObjectOrientation[0], m_sSelectedObject); //Setting up the Model Matrix
	}

	m_pCamera->PrintInfo();
	printf("FPS: %d\r", m_pSystem->FPS);//print the Frames per Second	
}

