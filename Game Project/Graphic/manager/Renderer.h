#pragma once

namespace graphic
{

	class cRenderer : public common::cSingleton<cRenderer>
	{
	public:
		cRenderer();
		virtual ~cRenderer();

		bool CreateDirectX(HWND hWnd, const int width, const int height);
		LPDIRECT3DDEVICE9 GetDevice() { return m_pDevice; }
		void Update(const float elpaseT);
		void RenderAxis();
		void RenderFPS();


	protected:


	private:
		LPDIRECT3DDEVICE9 m_pDevice;
		ID3DXFont *m_font;
		string m_fpsText;
		float m_elapseTime;
		int m_fps;
	};


	// ������ �ʱ�ȭ.
	bool InitRenderer(HWND hWnd, const int width, const int height);
	void ReleaseRenderer();
	inline cRenderer* GetRenderer() { return cRenderer::Get(); }
	inline LPDIRECT3DDEVICE9 GetDevice() { return cRenderer::Get()->GetDevice(); }
}
