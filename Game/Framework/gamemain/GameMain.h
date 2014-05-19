
#pragma once


namespace framework
{

	class cGameMain
	{
	public:
		cGameMain();
		virtual ~cGameMain();
		
		enum STATE
		{
			INIT,
			RUN,
			SHUTDOWN,			
		};

		virtual void Init(HWND hWnd);
		virtual void ShutDown();
		virtual void Run();
		virtual void Update(const float elapseT);
		virtual void Render(const float elapseT);

		const string& GetWindowName();
		const RECT& GetWindowRect();
		virtual void MessageProc( UINT message, WPARAM wParam, LPARAM lParam);


	protected:
		STATE m_state;
		HWND m_hWnd;
		string m_windowName;
		RECT m_windowRect;


	// singleton
	protected:
		static cGameMain* m_pInstance;
	public:
		static cGameMain* Get();
	};


	// �����ӿ�ũ ���� �Լ�.
	int FrameWorkWinMain(HINSTANCE hInstance, 
		HINSTANCE hPrevInstance, 
		LPSTR lpCmdLine, 
		int nCmdShow);

	// �����ӿ�ũ �ν��Ͻ��� �����Ѵ�. �ݵ�� �� �Լ��� �����ؾ� �Ѵ�.
	cGameMain* CreateFrameWork();
}
