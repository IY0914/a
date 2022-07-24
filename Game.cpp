/*
	Game.cpp
	�Q�[���ōs�����ۂ̏������Ăяo�����߁A���ۂɃN���X���֏������L�q���邽�߂̃t�@�C���B
	���̃t�@�C���ɃQ�[���̏������������āA�Q�[������낤�I

	�쐬�ҁ@�F�@�x��@�a��
	�쐬���@�F�@2021/03/15
*/

#include <DxLib.h>						//	������ł��g�����߁ADxLib.h���C���N���[�h���Ă���
#include "Game.h"

//	�R���X�g���N�^�ƌĂ΂��֐�
Game::Game() :
	sceneID(SceneID::PlayScene),
	screenWidth(0),
	screenHeight(0),
	oldTime((LONGLONG)0),
	nowTime((LONGLONG)0),
	deltaTime(0.0f),
	firstWait(false),
	pGameSystem(nullptr)
{
	
}

//	�f�X�g���N�^�ƌĂ΂��֐�
Game::~Game()
{
	
}


//	�Q�[���̏��������s���֐�
void Game::Initialize()
{
	//�eScene����Initialize�Ăяo������
	titleScene.Initialize(screenWidth, screenHeight);
	playScene.Initialize(screenWidth, screenHeight);
	resultScene.Initialize(screenWidth, screenHeight);

}

//	�Q�[���̍X�V�������s���֐�
void Game::Update()
{
	
	//�߂�������(old)
	oldTime = nowTime;

	//���ݎ���(now)
	nowTime = GetNowHiPerformanceCount();

	//�o�ߎ���(deltaTime)
	deltaTime = (float)((nowTime - oldTime) / 1000000.0f);

	//Scene�؂�ւ��p�t���O�ϐ�bool�錾
	bool changeSceneFlag = false;

	//�X�V�J�n����
	if (!firstWait && deltaTime < 1.0f)
	{
		firstWait = true;
	}
	else if (!firstWait)
	{
		return;
	}

	//�eScene�̍X�V����(Update)
	//Scene�I������AScene����`�F���W�������󂯎��(true)
	switch (sceneID)
	{
	case Game::SceneID::TitleScene:
		titleScene.Update(deltaTime);
		changeSceneFlag = titleScene.GetChangeSceneFlag();
		break;
	case Game::SceneID::PlayScene:
		playScene.Update(deltaTime);
		changeSceneFlag = playScene.GetChangeSceneFlag();
		break;
	case Game::SceneID::ResultScene:
		resultScene.Update(deltaTime);
		changeSceneFlag = resultScene.GetChangeSceneFlag();
		break;
	
	}

	//�eScene�̏����ݒ�Initialize���Ăяo��
	//�y�я����ݒ�ϐ����f
	if (changeSceneFlag)
	{
		switch (sceneID)
		{
		case Game::SceneID::TitleScene:
			sceneID = SceneID::PlayScene;
			playScene.Initialize(screenWidth, screenHeight);
			break;
		case Game::SceneID::PlayScene:
			sceneID = SceneID::ResultScene;
			resultScene.Initialize(screenWidth, screenHeight);
			break;
		case Game::SceneID::ResultScene:
			sceneID = SceneID::TitleScene;
			titleScene.Initialize(screenWidth, screenHeight);
			break;
		case Game::SceneID::OverID:
			sceneID = SceneID::PlayScene;
			playScene.Initialize(screenWidth, screenHeight);
			break;
		}
	}
	
}

//	�Q�[���̕`����s���֐��BDraw�Ə����ꍇ������
void Game::Render()
{
	
	//�eScene�̕`�揈��
	switch (sceneID)
	{
	case Game::SceneID::TitleScene:
		titleScene.Render();
		break;
	case Game::SceneID::PlayScene:
		playScene.Render();
		break;
	case Game::SceneID::ResultScene:
		resultScene.Render();
		break;
	}

	//�����`��E��
	DrawFormatString(screenWidth - 170, screenHeight - 20, GetColor(255, 255, 255), "�A�N�V�����Q�[���J��");

	//	�Q�[���̕`�揈���I���I
}

//	�Q�[���̏I���������s���֐��B����������K�v�ȏꍇ�iRelease�֐��Ȃǂ��Ăяo���j�́A���̊֐����ŏ�������
void Game::Finalize()
{
	
}

void Game::SetScreenSize(int width, int height)
{
	//�X�N���[���T�C�Y��WinMain.cpp���擾
	screenWidth = width;
	screenHeight = height;
}

void Game::SetGameSystemObjects(GameSystemObjects* pObj)
{
	//�O���t�@�C�����擾
	pGameSystem =  pObj;

	//�e�V�[�����f
	titleScene.SetGameSystemObject(pObj);
	playScene.SetGameSystemObject(pObj);
	resultScene.SetGameSystemObject(pObj);
}




