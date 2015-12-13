/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/
//using namespace std;

//using namespace Ogre;

#include "TutorialApplication.h"

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::Entity* wagon = mSceneMgr->createEntity(Ogre::SceneManager::PT_CUBE);
	wagon->setMaterialName("Examples/BumpyMetal");
	Ogre::SceneNode* wagonNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	wagonNode->attachObject(wagon);
	wagonNode->translate(Ogre::Vector3(0, 65, 100));
	wagonNode->scale(Ogre::Vector3(6, 1, 1));
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);

	Ogre::Light* directionalLight = mSceneMgr->createLight("DirectionalLight");
	directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(Ogre::ColourValue(.7, .7, 0));
	directionalLight->setSpecularColour(Ogre::ColourValue(.7, .7, 0));
	directionalLight->setDirection(Ogre::Vector3(0.7, -0.7, -1));

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		15000, 15000, 1, 1,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);
	Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/GrassFloor");

	mCamera->moveRelative(Ogre::Vector3(0, 400, 1500));
}
//---------------------------------------------------------------------------
//void TutorialApplication::createCamera()
//{
//	/*mCamera = mSceneMgr->createCamera("PlayerCam");
//	mCamera->setPosition(Ogre::Vector3(0, 300, 500));
//	mCamera->lookAt(Ogre::Vector3(0, 0, 0));
//	mCamera->setNearClipDistance(5);*/
//	//mCameraMan = new OgreBites::SdkCameraMan(mCamera);
//}



//void TutorialApplication::createViewports()
//{
//	
//}
//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
