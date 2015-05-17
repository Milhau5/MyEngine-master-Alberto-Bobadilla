#include "ApplicationClass.h"
void ApplicationClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.1f;
	//m_m4SelectedObject = m_pMeshMngr->GetModelMatrix(m_sSelectedObject);

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

#pragma region Model Positioning
	//Translation
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_m4ObjectTranslation *= glm::translate(MEIDENTITY, vector3(-fSpeed, 0.0f, 0.0f));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_m4ObjectTranslation *= glm::translate(MEIDENTITY, vector3( fSpeed, 0.0f, 0.0f));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if(bModifier)
			m_m4ObjectTranslation *= glm::translate(MEIDENTITY, vector3(0.0f, 0.0f,-fSpeed));
		else
			m_m4ObjectTranslation *= glm::translate(MEIDENTITY, vector3(0.0f, fSpeed, 0.0f));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if(bModifier)
			m_m4ObjectTranslation *= glm::translate(MEIDENTITY, vector3(0.0f, 0.0f, fSpeed));
			
		else
			m_m4ObjectTranslation *= glm::translate(MEIDENTITY, vector3(0.0f,-fSpeed, 0.0f));
	}

	//Orientation
	//With Euler Angles
#ifdef USINGEULER
	static vector3 v3Rotation;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if(bModifier)
			v3Rotation.x += fSpeed * 15.0f;
		else
			v3Rotation.x +=-fSpeed * 15.0f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		if(bModifier)
			v3Rotation.y += fSpeed * 15.0f;
		else
			v3Rotation.y +=-fSpeed * 15.0f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if(bModifier)
			v3Rotation.z += fSpeed * 15.0f;
		else
			v3Rotation.z +=-fSpeed * 15.0f;
	}
	m_m4ObjectOrientation =	glm::rotate(MEIDENTITY, v3Rotation.x, MEAXISX);
#ifdef USINGVISUALS
	m_pMeshMngr->AddTorusToQueue(m_m4ObjectTranslation * m_m4ObjectOrientation * glm::rotate(MEIDENTITY,90.0f,MEAXISZ) * glm::scale(vector3(3.0f)), MERED);  
#endif // USINGVISUALS
	m_m4ObjectOrientation*=	glm::rotate(MEIDENTITY, v3Rotation.y, MEAXISY);
#ifdef USINGVISUALS
	m_pMeshMngr->AddTorusToQueue(m_m4ObjectTranslation * m_m4ObjectOrientation * glm::scale(vector3(3.0f)), MEGREEN);  
#endif // USINGVISUALS
	m_m4ObjectOrientation*=	glm::rotate(MEIDENTITY, v3Rotation.z, MEAXISZ);
#ifdef USINGVISUALS
	m_pMeshMngr->AddTorusToQueue(m_m4ObjectTranslation * m_m4ObjectOrientation * glm::rotate(MEIDENTITY,90.0f,MEAXISX) * glm::scale(vector3(3.0f)), MEBLUE);  
#endif // USINGVISUALS  
	//reset orientation
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		v3Rotation = vector3(0.0f);
	}
#endif // USINGEULER
#ifdef USINGQUATERNIONS
	static vector3 v3Rotation;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if(bModifier)
			v3Rotation.x += glm::radians( fSpeed * 15.0f );
		else
			v3Rotation.x += glm::radians(-fSpeed * 15.0f );
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		if(bModifier)
			v3Rotation.y += glm::radians( fSpeed * 15.0f );
		else
			v3Rotation.y += glm::radians(-fSpeed * 15.0f );
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if(bModifier)
			v3Rotation.z += glm::radians( fSpeed * 15.0f );
		else
			v3Rotation.z += glm::radians(-fSpeed * 15.0f );
	}
	m_m4ObjectOrientation = glm::mat4_cast(quaternion(v3Rotation));
	
	//reset orientation
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		v3Rotation = vector3(0.0f);
	}
#endif // USINGQUATERNIONS
#ifdef USINGMATRICES
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if(bModifier)
			m_m4ObjectOrientation *= glm::rotate(MEIDENTITY, fSpeed * 15.0f, MEAXISX);
		else
			m_m4ObjectOrientation *= glm::rotate(MEIDENTITY,-fSpeed * 15.0f, MEAXISX);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		if(bModifier)
			m_m4ObjectOrientation *= glm::rotate(MEIDENTITY, fSpeed * 15.0f, MEAXISY);
		else
			m_m4ObjectOrientation *= glm::rotate(MEIDENTITY,-fSpeed * 15.0f, MEAXISY);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if(bModifier)
			m_m4ObjectOrientation *= glm::rotate(MEIDENTITY, fSpeed * 15.0f, MEAXISZ);
		else
			m_m4ObjectOrientation *= glm::rotate(MEIDENTITY,-fSpeed * 15.0f, MEAXISZ);
	}
#endif // USINGMATRICES
	
	//reset orientation
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_m4ObjectOrientation = MEIDENTITY;
	}
#pragma endregion

#pragma region Camera Positioning
	if(bModifier)
		fSpeed *= 10.0f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCamera->MoveForward(fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCamera->MoveForward(-fSpeed);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCamera->MoveSideways(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCamera->MoveSideways(fSpeed);
	m_pCamera->CalculateView();
#pragma endregion

#pragma region Model States
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState( m_sSelectedObject, 0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState( m_sSelectedObject, 1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState( m_sSelectedObject, 2);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState( m_sSelectedObject, 3);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState( m_sSelectedObject, 4);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState( m_sSelectedObject, 5);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState( m_sSelectedObject, 6);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState( m_sSelectedObject, 7);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState( m_sSelectedObject, 8);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState( m_sSelectedObject, 9);
	}
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape,NULL,PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
	ON_KEY_PRESS_RELEASE(F5,NULL,m_pMeshMngr->m_pModelMngr->GenerateOctree())
	static bool bVisible = false;
	ON_KEY_PRESS_RELEASE(F6, bVisible = !bVisible, m_pMeshMngr->m_pModelMngr->SetVisibleOctree(bVisible))
#pragma endregion
}
void ApplicationClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;

	static bool bLeft_Released = false;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		bLeft_Released = true;
	}
	else
	{
		if(bLeft_Released == true)
		{
			m_pMeshMngr->SetVisibleBoundingObject(false, "ALL");
			m_pMeshMngr->SetVisibleBoundingObjectHierarchy(false, "ALL");
			vector2 v2Object = m_pMeshMngr->m_pModelMngr->ShootRay( sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, m_pCamera, false);
			String sInstance = m_pMeshMngr->GetNameOfInstanceByIndex(static_cast<int>(v2Object.x));
			if(sInstance != "")
			{
				m_pMeshMngr->SetVisibleBoundingObject(true, sInstance);
				m_pMeshMngr->SetVisibleBoundingObjectHierarchy(true, sInstance);
				m_sSelectedObject = sInstance;
				m_m4ObjectTranslation = m_pMeshMngr->GetModelMatrix(m_sSelectedObject);
			}
		}
		bLeft_Released = false;
	}
}
void ApplicationClass::ProcessJoystick(void)
{
	float fDirection = 1.0f;
	int nPad = 0;
	sf::Joystick::update();
	if(sf::Joystick::isConnected(nPad))
	{
#pragma region Camera Position / Orientation
		if(sf::Joystick::isButtonPressed(nPad, 4) && sf::Joystick::isButtonPressed(nPad, 5))
			exit(0);

		static float fAngleX = 0.0f;
		static float fAngleY = 0.0f;

		if(sf::Joystick::isButtonPressed(nPad, 8) && sf::Joystick::isButtonPressed(nPad, 9))	
		{
			fAngleX = 0.0f;
			fAngleY = 0.0f;
			m_pCamera->SetPosition(glm::vec3( 0.0f, 0.0f, 10.0f));
		}

		float fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::Y);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta /= 1000.0f;
			m_pCamera->MoveForward(-fDelta);
		}
		
		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::X);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta /= 1000.0f;
			m_pCamera->MoveSideways(fDelta);
		}

		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::Z);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta /= 1000.0f;
			m_pCamera->MoveVertical(fDelta);
		}

		fDelta = -sf::Joystick::getAxisPosition(nPad, sf::Joystick::R);
		if(fDelta > 25 || fDelta < -25)
		{
			fAngleX -= fDelta/10000.0f;
		}
		
		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::U);
		if(fDelta > 25 || fDelta < -25)
		{
			fAngleY -= fDelta/10000.0f;
		}

		m_pCamera->Rotate(fAngleX, fAngleY);
		m_pCamera->CalculateView();
#pragma endregion
	}
}
void ApplicationClass::CameraRotation(float a_fSpeed)
{
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = m_pSystem->WindowX + m_pSystem->WindowWidth / 2;
	CenterY = m_pSystem->WindowY + m_pSystem->WindowHeight / 2;
	
	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);
	
	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	static float fAngleX = 0.0f;
	static float fAngleY = 0.0f;

	if(MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		fAngleY += DeltaMouse * a_fSpeed;
	}
	else if(MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		fAngleY -= DeltaMouse * a_fSpeed;
	}

	if(MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		fAngleX -= DeltaMouse * a_fSpeed;
	}
	else if(MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		fAngleX += DeltaMouse * a_fSpeed;
	}
	m_pCamera->Rotate(fAngleX, fAngleY);
}
void ApplicationClass::ArcBall(float a_fSensitivity)
{
	static matrix4 arcball;
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = m_pSystem->WindowX + m_pSystem->WindowWidth / 2;
	CenterY = m_pSystem->WindowY + m_pSystem->WindowHeight / 2;
	
	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);
	
	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	static float fVerticalAngle = 0.0f;
	static float fHorizontalAngle = 0.0f;

	float fSpeed = 0.001f;

	if(MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		arcball = glm::rotate(arcball, a_fSensitivity * DeltaMouse, vector3(0.0f, 1.0f, 0.0f));
	}
	else if(MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		arcball = glm::rotate(arcball, -a_fSensitivity * DeltaMouse, vector3(0.0f, 1.0f, 0.0f));
	}

	if(MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		arcball = glm::rotate(arcball, a_fSensitivity * DeltaMouse, vector3(1.0f, 0.0f, 0.0f));
	}
	else if(MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		arcball = glm::rotate(arcball, -a_fSensitivity * DeltaMouse, vector3(1.0f, 0.0f, 0.0f));
	}
	m_m4ObjectOrientation = arcball;
}