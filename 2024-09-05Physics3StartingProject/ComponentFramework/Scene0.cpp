#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene0.h"
#include <MMath.h>
#include "Debug.h"
#include "TransformComponent.h"
#include "MaterialComponent.h"
#include <QMath.h>
#include "XMLAssetManager.h"
#include "ShaderComponent.h"
#include "MeshComponent.h"
#include "ShapeComponent.h"
#include "PhysicsComponent.h"
#include "Ray.h"
#include "PhysicsSystem.h"
bool Scene0::OnCreate()
{
	XMLAssetManager assetManager;
	// Make sure these names match the stuff in your xml file:
	std::vector<std::string> names{
		"ActorGameBoard" , "ActorChecker1", "ActorChecker2",
		"ActorSkull", "ActorCube", "ActorMario"
		
		
	};
	for (const auto& name : names) {
		auto asset = assetManager.xmlAssets.find(name);
		actors[name] = asset->second;
	}
	camera = std::dynamic_pointer_cast<CameraActor>(assetManager.xmlAssets.find("Camera1")->second);
	light = std::dynamic_pointer_cast<LightActor>(assetManager.xmlAssets.find("Light1")->second);
	return true;
}

void Scene0::OnDestroy()
{
	actors.clear();
}


void Scene0::HandleEvents(const SDL_Event& sdlEvent)
{
	Ref<TransformComponent> cameraTransform = camera->GetComponent <TransformComponent>();
	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT) {

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT) {

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP) {

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN) {

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			cameraTransform->SetTransform(cameraTransform->pos, cameraTransform->GetOrientation() * QMath::angleAxisRotation(2.0f, Vec3(0.0f, 1.0f, 0.0f)));
			camera->UpdateViewMatrix();
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A) {
			cameraTransform->SetTransform(cameraTransform->pos, cameraTransform->GetOrientation() * QMath::angleAxisRotation(-2.0f, Vec3(0.0f, 1.0f, 0.0f)));
			camera->UpdateViewMatrix();

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W) {
			cameraTransform->SetTransform(cameraTransform->pos, cameraTransform->GetOrientation() * QMath::angleAxisRotation(2.0f, Vec3(1.0f, 0.0f, 0.0f)));
			camera->UpdateViewMatrix();

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S) {
			cameraTransform->SetTransform(cameraTransform->pos, cameraTransform->GetOrientation() * QMath::angleAxisRotation(-2.0f, Vec3(1.0f, 0.0f, 0.0f)));
			camera->UpdateViewMatrix();

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_M) {
			renderMeshes = !renderMeshes;
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_C) {
			renderCollisionShapes = !renderCollisionShapes;
		}

		break;

	case SDL_MOUSEBUTTONDOWN:
		if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
			Vec3 mouseCoords(static_cast<float>(sdlEvent.button.x), static_cast<float>(sdlEvent.button.y), 0.0f);
			//mouseCoords.print("Pixel space:");

			Matrix4 ndcToPixelSpace = MMath::viewportNDC(1280, 720);
			Matrix4 pixelToNdc = MMath::inverse(ndcToPixelSpace);

			//Scott meshes around with w component of vec4 for perpestive
			Vec4 mouseCoordsNDC = pixelToNdc * mouseCoords;
			//Put mouse on front of the ndc plane
			mouseCoordsNDC.z = -1.0f;
			//mouseCoordsNDC.print("NDC space:");

			Matrix4 cameraToNdc = camera->GetProjectionMatrix();
			Matrix4 ndcToCameraSpace = MMath::inverse(cameraToNdc);

			Vec4 mouseCoordsCameraSpace = ndcToCameraSpace * mouseCoordsNDC;
			//mouseCoordsCameraSpace.print("Camera space:");
			//the w coordine gets messed up by the projection matrix
			//Song ho has us covered here:
			//https://www.songho.ca/math/homogeneous/homogeneous.html

			//we live in 3d
			//so we dide out the w component such that it is 1
			mouseCoordsCameraSpace = VMath::perspectiveDivide(mouseCoordsCameraSpace);
			//mouseCoordsCameraSpace.print("Mouse space with w divided:"); //w is now 1

			Matrix4 worldToCameraSpace = camera->GetViewMatrix();
			Matrix4 cameraToWorldSpace = MMath::inverse(worldToCameraSpace);
			Vec4 mouseCoordsWorldSpace = cameraToWorldSpace * mouseCoordsCameraSpace;
			//mouseCoordsWorldSpace.print("World space:");

			Vec3 rayStartWorldSpace = mouseCoordsWorldSpace;
			Vec3 rayDirWorldSpace = mouseCoordsWorldSpace - camera->GetComponent<TransformComponent>()->pos;
			rayDirWorldSpace = VMath::normalize(rayDirWorldSpace);




			GEOMETRY::Ray rayWorldSpace(rayStartWorldSpace, rayDirWorldSpace);

			for (auto it = actors.begin(); it != actors.end(); ++it) {
				Ref<Actor> actor = std::dynamic_pointer_cast<Actor>(it->second);
				Ref<TransformComponent> transformComponent = actor->GetComponent <TransformComponent>();
				Ref<ShapeComponent> shapeComponent = actor->GetComponent <ShapeComponent>();
				// TODO for Assignment 2: 
				// Transform the ray into the local space (ie Paul Neale space) of the object and check if a collision occured
				// Lets do just spheres for now to help us debug
				if (shapeComponent->shapeType == ShapeType::sphere || shapeComponent->shapeType == ShapeType::cylinder 
					|| shapeComponent->shapeType == ShapeType::capsule || shapeComponent->shapeType == ShapeType::box) {
					// Transform the ray into the local space (ie Paul Neale space) of the object
					//for checker u would need to find the modelmatrix of the parent of the object
					//it should be around the getmodelmatrix function
					Matrix4 paulNealeToWorldSpace =   actor->GetModelMatrix() ;
					Matrix4 worldToPaulNealeSpace = MMath::inverse(paulNealeToWorldSpace);
					// Transform the start of the ray
					Vec3 rayStartPaulNealeSpace = worldToPaulNealeSpace * rayWorldSpace.start;
					// Transform the direction of the ray
					// Be careful, we don't want to translate the direction. 
					// Only rotate using quaternion
					Quaternion paulNealeToWorldSpaceRotation =  actor->Orientation();
					Quaternion worlToPaulNealeSpaceRotation = QMath::conjugate(paulNealeToWorldSpaceRotation);
					Vec3 rayDirPaulNealeSpace = QMath::rotate(rayWorldSpace.dir, worlToPaulNealeSpaceRotation);
					GEOMETRY::Ray rayPaulNealeSpace(rayStartPaulNealeSpace, rayDirPaulNealeSpace);
					// Shoot the ray at the sphere
					rayInfo = shapeComponent->shape->rayIntersectionInfo(rayPaulNealeSpace);
					if (rayInfo.isIntersected) {
						std::cout << "You picked: " << it->first << '\n';
						pickedActor = actor; // make a member variable called pickedActor. Will come in handy later…
						haveClickedOnSomething = true; // make this a member variable too. Set it to false before we loop over each actor
						//Todo 
						//Find the mouse pos in world space based on the ray intersection
						//mousePosWorld = .....
						

						intersectionPoint = transformComponent->GetTransformMatrix() * rayInfo.intersectionPoint;
					}
				}
				
			}
			break;
		}

	default:
		break;
		}
}

void Scene0::Update(const float deltaTime)
{
	if (haveClickedOnSomething) {
		Ref<PhysicsComponent> physicsComponent = pickedActor->GetComponent<PhysicsComponent>();
		Vec3 gravityAccel(0.0f, -9.8f, 0.0f);
		Vec3 gravityForce = physicsComponent->mass * gravityAccel;
		//drag = -c * vel
		float dragCoeff = 0.25f;
		Vec3 dragForce = physicsComponent->vel * -(dragCoeff);
		Vec3 netForce = gravityForce + dragForce;

		//Write all this functions.
		PhysicsSystem::ApplyForce(physicsComponent,netForce);
		PhysicsSystem::UpdateVel(physicsComponent, deltaTime); 
		

		/*float slope = 1.0f;
		float yIntercept = 1.0f;
		PhysicsSystem::StraightLineConstant(physicsComponent, slope, yIntercept, deltaTime);*/
		
		PhysicsSystem::MouseConstraint(physicsComponent, intersectionPoint, deltaTime);
		PhysicsSystem::UpdatePos(physicsComponent, deltaTime);
		PhysicsSystem::UpdateOrientation(physicsComponent, deltaTime);
		//Make sure transform matches physics
		PhysicsSystem::UpdateTransform(pickedActor);
		
	}
}

void Scene0::Render() const
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(GL_UNIFORM_BUFFER, camera->GetMatricesID());
	glBindBuffer(GL_UNIFORM_BUFFER, light->GetLightID());
	// Let it go
	glBindTexture(GL_TEXTURE_2D, 0);

	for (auto it = actors.begin(); it != actors.end(); ++it) {
		Ref<Actor> actor = std::dynamic_pointer_cast<Actor>(it->second);
		glUseProgram(actor->GetComponent<ShaderComponent>()->GetProgram());
		glUniformMatrix4fv(actor->GetComponent<ShaderComponent>()->GetUniformID("modelMatrix"), 1, GL_FALSE, actor->GetModelMatrix());
		glBindTexture(GL_TEXTURE_2D, actor->GetComponent<MaterialComponent>()->getTextureID());
		if (renderMeshes) {
			actor->GetComponent<MeshComponent>()->Render(GL_TRIANGLES);
		}
		if (renderCollisionShapes) {
			// Drawing the primitive geometry associated with the mesh to help debug ray intersects, culling, and collision detection
			actor->GetComponent<ShapeComponent>()->Render();
		}
	}
}

