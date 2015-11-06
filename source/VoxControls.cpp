#include "VoxGame.h"

// Controls
void VoxGame::UpdateControls(float dt)
{
	UpdateKeyboardControls(dt);
	UpdateMouseControls(dt);
	UpdateGamePadControls(dt);
}

void VoxGame::UpdateKeyboardControls(float dt)
{
	GameMode gameMode = GetGameMode();

	if (gameMode == GameMode_Debug)
	{
		// Keyboard camera movements
		if (m_bKeyboardForward)
		{
			m_pGameCamera->Fly(20.0f * dt);
		}
		if (m_bKeyboardBackward)
		{
			m_pGameCamera->Fly(-20.0f * dt);
		}
		if (m_bKeyboardStrafeLeft)
		{
			m_pGameCamera->Strafe(-20.0f * dt);
		}
		if (m_bKeyboardStrafeRight)
		{
			m_pGameCamera->Strafe(20.0f * dt);
		}
	}

	if (gameMode == GameMode_Game)
	{
		// Player movements
		if (m_bKeyboardSpace)
		{
			m_pPlayer->Jump();
		}


		bool resetMovementVector = false;
		bool l_moving = true;
		float speedDescreaseFactor = 1.0f;
		if (m_bKeyboardForward == false && m_bKeyboardBackward == false && m_bKeyboardStrafeLeft == false && m_bKeyboardStrafeRight == false)
		{
			l_moving = false;

			// Reduce the movement speed (drag)
			m_movementSpeed -= m_maxMovementSpeed / (m_movementDragTime / dt);

			if (m_movementSpeed <= 0.0f)
			{
				m_movementSpeed = 0.0f;
				m_keyboardMovement = false;
				m_pPlayer->StopMoving();
			}
		}
		else
		{
			m_keyboardMovement = true;

			// Increase the movement speed since we are pressing a movement key
			m_movementSpeed += m_maxMovementSpeed / (m_movementIncreaseTime / dt);

			// Don't allow faster than max movement
			if (m_movementSpeed > m_maxMovementSpeed)
			{
				m_movementSpeed = m_maxMovementSpeed;
			}
		}

		if (m_bKeyboardForward)
		{
			if (resetMovementVector == false)
			{
				m_movementDirection = vec3(0.0f, 0.0f, 0.0f);
				resetMovementVector = true;
			}

			vec3 cameraRight = m_pGameCamera->GetRight();
			vec3 playerUp = m_pPlayer->GetUpVector();
			vec3 moveDirection = normalize(cross(cameraRight, playerUp));
			m_movementDirection -= moveDirection;
		}

		if (m_bKeyboardBackward)
		{
			if (resetMovementVector == false)
			{
				m_movementDirection = vec3(0.0f, 0.0f, 0.0f);
				resetMovementVector = true;
			}

			vec3 cameraRight = m_pGameCamera->GetRight();
			vec3 playerUp = m_pPlayer->GetUpVector();
			vec3 moveDirection = normalize(cross(cameraRight, playerUp));
			m_movementDirection += moveDirection;
		}

		if (m_bKeyboardStrafeLeft)
		{
			if (resetMovementVector == false)
			{
				m_movementDirection = vec3(0.0f, 0.0f, 0.0f);
				resetMovementVector = true;
			}

			vec3 cameraRight = m_pGameCamera->GetRight();
			vec3 playerUp = m_pPlayer->GetUpVector();
			vec3 playerRight = normalize(cross(playerUp, cameraRight));
			vec3 moveDirection = normalize(cross(playerUp, playerRight));
			m_movementDirection += moveDirection;
		}

		if (m_bKeyboardStrafeRight)
		{
			if (resetMovementVector == false)
			{
				m_movementDirection = vec3(0.0f, 0.0f, 0.0f);
				resetMovementVector = true;
			}

			vec3 cameraRight = m_pGameCamera->GetRight();
			vec3 playerUp = m_pPlayer->GetUpVector();
			vec3 playerRight = normalize(cross(playerUp, cameraRight));
			vec3 moveDirection = normalize(cross(playerUp, playerRight));
			m_movementDirection -= moveDirection;
		}

		if (length(m_movementDirection) > 0.001f && m_movementSpeed > m_movementStopThreshold)
		{
			m_movementDirection = normalize(m_movementDirection);
			m_pPlayer->MoveAbsolute(m_movementDirection, m_movementSpeed*speedDescreaseFactor * dt, true);
		}
	}
}

void VoxGame::UpdateMouseControls(float dt)
{
	int x = m_pVoxWindow->GetCursorX();
	int y = m_pVoxWindow->GetCursorY();

	GameMode gameMode = GetGameMode();

	if (gameMode == GameMode_Debug)
	{
		// Mouse camera movements
		if (m_bCameraRotate)
		{
			MouseCameraRotate(x, y);
		}
		if (m_bCameraZoom)
		{
			MouseCameraZoom(x, y);
		}
	}
}

void VoxGame::UpdateGamePadControls(float dt)
{

}