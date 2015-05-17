/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __CAMERASINGLETON_H_
#define __CAMERASINGLETON_H_

#include "ME\system\SystemSingleton.h"

namespace MyEngine
{

class MyEngineDLL CameraSingleton
{
	float m_fFieldOfView;	//Field of view of the camera
	float m_fAspectRatio;	//Aspect ratio of the view
	float m_fNear;			//Near clipping plane
	float m_fFar;			//Far clipping plane

	static CameraSingleton* m_pInstance;//Singleton
	SystemSingleton* m_pSystem; //System pointer

	matrix4 m_m4Projection; //Projection
	matrix4 m_m4View; //View
	matrix4 m_m4ViewInverse; //Inverse of the view
	matrix4 m_m4MVP; //MVP

	matrix4 m_m4VPInverse; // Inverse of the View-Projection matrix

	vector3 m_v4Position; //CameraPosition
	vector3 m_v3Forward; //Camera view vector
	vector3 m_v3Up; //Camera up vector

	
public:
	/* Gets/Constructs the singleton pointer */
	static CameraSingleton* GetInstance();
	/* Destroys the singleton */
	static void ReleaseInstance(void);

	/* Rotates the camera at an specified Euler angle */
	void Rotate(float a_fAngX, float a_fAngY);

	/* Translates the camera forward or backward */
	void MoveForward(float a_fDistance = 0.1f);
	/* Translates the camera horizontally */
	void MoveSideways(float a_fDistance = 0.1f);
	/* Translates the camera vertically */
	void MoveVertical(float a_fDistance = 0.1f);

	/* Sets the camera position by the specified vector3 */
	void SetPosition(vector3 a_v3Position);
	/* Gets the position of the camera in world space */
	vector3 GetPosition(void);

	/* Sets the direction of the view vector of the camera*/
	void SetForwardVector(vector3 a_v3Forward);
	/* Gets the view direction vector in world space */
	vector3 GetForwardVector(void);

	/* Sets the up vector of the camera */
	void SetUpVector(vector3 a_v3Direction);
	/* Gets the up vector of the camera in world space */
	vector3 GetUpVector(void);

	/* Calculates the view of the camera */
	void CalculateView();
	/* Sets the view of the camera by the specified matrix */
	void SetView(matrix4 a_m4View);
	/* Gets the view of the camera singleton*/
	matrix4 GetView(void);
	/* Property SetView/GetView*/
	__declspec(property(put = SetView, get = GetView)) matrix4 View;

	/* Gets the view of the camera singleton*/
	matrix4 GetViewInverse(void);

	/* Returns a matrix that would position a 1x1 plane right in front of camera */
	matrix4 GetCameraPlane(void);

	/* Returns the space 1.2085 units in front of camera (where 1 is the top border and -1 is the bottom border */
	matrix4 GetCameraSpaceAdjusted(void);

	/* Calculates the projection of the camera */
	void CalculateProjection();
	/* Sets the projection of the camera by the specified matrix */
	void SetProjection(matrix4 a_m4Projection);
	/* Asks the camera singleton for the projection */
	matrix4 GetProjection();
	/* Property SetProjection/GetProjection*/
	__declspec(property(put = SetProjection, get = GetProjection)) matrix4 Projection;
	
	/* Gets the inverse of the View Projection matrix of the camera */
	matrix4 GetInverseVP();
	/* Gets the Model-View-Projection matrix of the camera */
	matrix4 GetMVP();
	/* Gets the Model-View-Projection matrix of the camera specifying the model view matrix*/
	matrix4 GetMVP(matrix4 a_m4ToWorld);
	/* Property GetMVP*/
	__declspec(property(get = GetMVP)) matrix4 VMP;

	/* Sets the camera to be looking at the specified point in global space */
	void SetView(vector3 a_v3Target);

	/* Asks the camera for its field of view */
	float GetFieldOfView(void);
	/* Asks the camera for its near clipping plane */
	float GetNear(void);
	/* Asks the camera for its far clipping plane */
	float GetFar(void);

	void PrintInfo(void);

private:
	/* Constructor */
	CameraSingleton(void);
	/* Copy Constructor*/
	CameraSingleton(CameraSingleton const& other);
	/* Copy Assignment Operator*/
	CameraSingleton& operator=(CameraSingleton const& other);
	/* Destructor */
	~CameraSingleton(void);

	/* Releases the object from memory */
	void Release(void);
	/* Initialized the object's fields*/
	void Init(void);
};

}
#endif //_CAMERA_H