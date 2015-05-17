#include "ApplicationClass.h"
void ApplicationClass::InitUserAppVariables()
{
	switch (0)
	{
	default:
		m_pCamera->SetPosition(vector3(0.0f,0.0f,10.0f));
		break;
	case 1:
		m_pCamera->SetPosition(vector3(0.0f,3.0f,11.5f));
		break;
	}
	
	m_pMeshMngr->LoadModelUnthreaded("Minecraft\\MC_Steve.obj", "Steve");

	m_sSelectedObject = "Steve";
}

void ApplicationClass::Update (void)
{
	m_pSystem->UpdateTime();//Update the system
	m_pMeshMngr->Update(); //Update the mesh information
	float fTimeSpan = m_pSystem->LapClock();
	static float fRunTime = 0.0f;
	fRunTime += fTimeSpan;

	//First person camera movement
	if(m_bFPC == true)
		CameraRotation();

	if(m_bArcBall == true)
	{
		ArcBall();
		m_pMeshMngr->SetModelMatrix(m_m4ObjectTranslation * m_m4ObjectOrientation, m_sSelectedObject); //Setting up the Model Matrix
	}

	float fLenght = 3.0f;
	if(fRunTime > fLenght) //restart after 3 seconds
		fRunTime = 0.0f;
	float fPercent = MapValue(fRunTime, 0.0f, fLenght, 0.0f, 1.0f); //get a percentage out of fRunTime (0.00 to 0.99)

	vector3 v3Start(-3.0f, 0.0f, 0.0f);
	vector3 v3End(3.0f, 0.0f, 0.0f); //formerly 361.0f for Z
#ifdef USINGLERP
	vector3 v3Lerp;
	//v3Lerp.x = MapValue(fPercent, 0.0f, 1.0f, v3Start.x, v3End.x);
	//v3Lerp.y = MapValue(fPercent, 0.0f, 1.0f, v3Start.y, v3End.y);
	//v3Lerp.z = MapValue(fPercent, 0.0f, 1.0f, v3Start.z, v3End.z);
	v3Lerp = glm::lerp(v3Start,v3End,fPercent);
	//Now do interpolation:
	/*m_m4ObjectOrientation =	glm::rotate(MEIDENTITY, v3Lerp.x, MEAXISX) *
								glm::rotate(MEIDENTITY, v3Lerp.y, MEAXISY) *
								glm::rotate(MEIDENTITY, v3Lerp.z, MEAXISZ);*/
	m_m4ObjectTranslation = glm::translate(v3Lerp);
#endif // USINGLERP

#ifdef USINGSLERP
	v3Start = vector3(glm::radians(v3Start.x),glm::radians(v3Start.y),glm::radians(v3Start.z));
	v3End = vector3(glm::radians(v3End.x),glm::radians(v3End.y),glm::radians(v3End.z));
	//mix assigns it to SLERP, then cast that into a Matrix4
	m_m4ObjectOrientation = glm::mat4_cast(glm::mix(	quaternion(v3Start), quaternion(v3End),	fPercent));
#endif // USINGSLERP


	m_pMeshMngr->SetModelMatrix(m_m4ObjectTranslation * m_m4ObjectOrientation, m_sSelectedObject);
	m_pMeshMngr->AddAxisToQueue(m_m4ObjectTranslation * m_m4ObjectOrientation * glm::scale(vector3(3.0f)));

	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//m_pCamera->PrintInfo();
	printf("FPS: %d, Percent: %.3f, Time: %.3f     \r", m_pSystem->FPS, fPercent, fRunTime);//print the Frames per Second
}