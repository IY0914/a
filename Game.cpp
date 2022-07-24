/*
	Game.cpp
	ゲームで行う実際の処理を呼び出すため、実際にクラス内へ処理を記述するためのファイル。
	このファイルにゲームの処理を実装して、ゲームを作ろう！

	作成者　：　堀川　和雅
	作成日　：　2021/03/15
*/

#include <DxLib.h>						//	こちらでも使うため、DxLib.hをインクルードしておく
#include "Game.h"

//	コンストラクタと呼ばれる関数
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

//	デストラクタと呼ばれる関数
Game::~Game()
{
	
}


//	ゲームの初期化を行う関数
void Game::Initialize()
{
	//各SceneからInitialize呼び出し準備
	titleScene.Initialize(screenWidth, screenHeight);
	playScene.Initialize(screenWidth, screenHeight);
	resultScene.Initialize(screenWidth, screenHeight);

}

//	ゲームの更新処理を行う関数
void Game::Update()
{
	
	//過ぎた時間(old)
	oldTime = nowTime;

	//現在時間(now)
	nowTime = GetNowHiPerformanceCount();

	//経過時間(deltaTime)
	deltaTime = (float)((nowTime - oldTime) / 1000000.0f);

	//Scene切り替え用フラグ変数bool宣言
	bool changeSceneFlag = false;

	//更新開始処理
	if (!firstWait && deltaTime < 1.0f)
	{
		firstWait = true;
	}
	else if (!firstWait)
	{
		return;
	}

	//各Sceneの更新処理(Update)
	//Scene終了次第、Sceneからチェンジ処理を受け取る(true)
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

	//各Sceneの初期設定Initializeを呼び出し
	//及び初期設定変数反映
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

//	ゲームの描画を行う関数。Drawと書く場合もある
void Game::Render()
{
	
	//各Sceneの描画処理
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

	//文字描画右下
	DrawFormatString(screenWidth - 170, screenHeight - 20, GetColor(255, 255, 255), "アクションゲーム開発");

	//	ゲームの描画処理終了！
}

//	ゲームの終了処理を行う関数。解放処理が必要な場合（Release関数などを呼び出す）は、この関数内で処理する
void Game::Finalize()
{
	
}

void Game::SetScreenSize(int width, int height)
{
	//スクリーンサイズをWinMain.cppより取得
	screenWidth = width;
	screenHeight = height;
}

void Game::SetGameSystemObjects(GameSystemObjects* pObj)
{
	//外部ファイルより取得
	pGameSystem =  pObj;

	//各シーン反映
	titleScene.SetGameSystemObject(pObj);
	playScene.SetGameSystemObject(pObj);
	resultScene.SetGameSystemObject(pObj);
}

void Game::GetCharacterPosition()
{
	Character.getPosition(x,y);
}


