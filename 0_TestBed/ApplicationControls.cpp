#include "ApplicationClass.h"
void ApplicationClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.1f;
	//m_m4SelectedObject = m_pMeshMngr->GetModelMatrix(m_sSelectedObject);

#pragma region ON PRESS/RELEASE DEFINITIONS
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
#define ON_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		fSpeed += 1.0f;
		bModifier = true;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		fSpeed += 1.0f;
		bModifier = true;
	}
#pragma endregion

#pragma region Model Positioning
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(bModifier)
			m_m4ObjectOrientation[0] *= glm::rotate(matrix4(), 1.0f, vector3(0.0f, 0.0f, 1.0f));
		else
			m_m4ObjectTranslation[0] *= glm::translate(matrix4(), vector3(-fSpeed, 0.0f, 0.0f));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if(bModifier)
			m_m4ObjectOrientation[0] *= glm::rotate(matrix4(), 1.0f, vector3(0.0f, 0.0f,-1.0f));
		else
			m_m4ObjectTranslation[0] *= glm::translate(matrix4(), vector3( fSpeed, 0.0f, 0.0f));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if(bModifier)
			m_m4ObjectOrientation[0] *= glm::translate(matrix4(), vector3(0.0f, 0.0f, fSpeed - 1.0f));
		else
			m_m4ObjectOrientation[0] *= glm::translate(matrix4(), vector3(0.0f, fSpeed, 0.0f));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if(bModifier)
			m_m4ObjectOrientation[0] *= glm::translate(matrix4(), vector3(0.0f, 0.0f,-fSpeed + 1.0f));
			
		else
			m_m4ObjectOrientation[0] *= glm::translate(matrix4(), vector3(0.0f,-fSpeed, 0.0f));
	}
#pragma endregion

#pragma region Camera Positioning
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

#pragma region Other Actions
	ON_PRESS_RELEASE(Escape,,PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
	ON_PRESS_RELEASE(F5,,m_pMeshMngr->m_pModelMngr->GenerateOctree())
	static bool bVisible = false;
	ON_PRESS_RELEASE(F6, bVisible = !bVisible, m_pMeshMngr->m_pModelMngr->SetVisibleOctree(bVisible))
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
			m_pMeshMngr->SetVisibleBoundingObject(false);
			vector2 v2Object = m_pMeshMngr->m_pModelMngr->ShootRay(
														sf::Mouse::getPosition().x,
														sf::Mouse::getPosition().y,
														m_pCamera,
														false
													);
			String sInstance = m_pMeshMngr->GetNameOfInstanceByIndex(static_cast<int>(v2Object.x));
			if(sInstance != "")
			{
				m_pMeshMngr->SetVisibleBoundingObject(true, sInstance);
				m_sSelectedObject = sInstance;
				m_m4ObjectTranslation[0] = m_pMeshMngr->GetModelMatrix(m_sSelectedObject);
				m_pMeshMngr->SetVisibleBoundingObjectHierarchy(true, m_sSelectedObject);
			}
		}
		bLeft_Released = false;
	}
}
void ApplicationClass::ProcessJoystick(void)
{
	float fDirection = 1.0f;
	int nPad = 0;
	for(nPad = 0; nPad < m_nPads; nPad++)
	{
		if(m_Wiimote[nPad].IsConnected())
		{
			m_Wiimote[nPad].RefreshState();
#pragma region ON PRESS/RELEASE DEFINITION
			static bool bLastA = false, bLastB = false, bLastPlus = false, bLastMinus = false,
						bLastUp = false, bLastDown = false, bLastLeft = false, bLastRight = false,
						bLastOne = false, bLastTwo = false, bLastHome = false;
#define ON_PRESS_RELEASE(button, pressed_action, released_action){  \
			bool pressed = m_Wiimote[nPad].Button.button();			\
			if(pressed){											\
				if(!bLast##button) pressed_action;}/*Just pressed? */\
			else if(bLast##button) released_action;/*Just released?*/\
			bLast##button = pressed; } //remember the state
#pragma endregion
#pragma region Position and Orientation
			bool bModifier = m_Wiimote[nPad].Button.B();
			if(m_Wiimote[nPad].Button.Up())
			{
				if(bModifier)
					m_m4ObjectTranslation[nPad] = glm::translate(matrix4(), MEAXISZ *-0.1f) * m_m4ObjectTranslation[nPad];
				else
					m_m4ObjectTranslation[nPad] = glm::translate(matrix4(), MEAXISY * 0.1f) * m_m4ObjectTranslation[nPad];
			}
			else if(m_Wiimote[nPad].Button.Down())
			{
				if(bModifier)
					m_m4ObjectTranslation[nPad] = glm::translate(matrix4(), MEAXISZ * 0.1f) * m_m4ObjectTranslation[nPad];
				else
					m_m4ObjectTranslation[nPad] = glm::translate(matrix4(), MEAXISY *-0.1f) * m_m4ObjectTranslation[nPad];
			}

			if(m_Wiimote[nPad].Button.Left())
			{
				m_m4ObjectTranslation[nPad] = glm::translate(matrix4(), MEAXISX * -0.1f * fDirection) * m_m4ObjectTranslation[nPad];
			}
			else if(m_Wiimote[nPad].Button.Right())
			{
				m_m4ObjectTranslation[nPad] = glm::translate(matrix4(), MEAXISX * 0.1f * fDirection) * m_m4ObjectTranslation[nPad];
			}

			float fAngleX = -m_Wiimote[nPad].Acceleration.Orientation.Pitch;
			m_m4ObjectOrientation[nPad] = glm::rotate(matrix4(), -fAngleX * fDirection, MEAXISX);

			float fAngleZ = m_Wiimote[nPad].Acceleration.Orientation.Roll;
			m_m4ObjectOrientation[nPad] *= glm::rotate(matrix4(), -fAngleZ * fDirection, MEAXISZ);

			if(fDirection > 0)
				m_m4ObjectOrientation[nPad] *= glm::rotate(matrix4(), 180.0f, MEAXISY);
#pragma endregion
#pragma region Other
			ON_PRESS_RELEASE(Home,,PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))

			if(m_Wiimote[nPad].Button.Two())
				m_pMeshMngr->SetVisibleBoundingObject(true, nPad);
			else
				m_pMeshMngr->SetVisibleBoundingObject(false, nPad);
			
			//m_Wiimote[nPad].SetRumble(m_Wiimote[nPad].Button.A());

			ON_PRESS_RELEASE(A,,m_pMeshMngr->m_pModelMngr->GenerateOctree())
			static bool bVisible = false;
			ON_PRESS_RELEASE(One, bVisible = !bVisible, m_pMeshMngr->m_pModelMngr->SetVisibleOctree(bVisible))
#pragma endregion
		}
	}
	
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
	m_m4ObjectOrientation[0] = arcball;
}