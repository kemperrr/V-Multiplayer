/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Direct3Device9.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Direct3Device9 interface hook source file
=============================================================*/

#include "Main.h"

extern CChatBox			*pChatBox;
extern CChatInput		*pChatInput;
extern CClient			*pClient;
extern CGame			*pGame;

CIDirect3DDevice9::CIDirect3DDevice9(IDirect3D9 *pD3D, IDirect3DDevice9 *pOriginal)
{ 
	// Save Direct3D9 device
	m_pIDirect3DDevice9 = pOriginal;
	// Save Direct3D9 handle
	m_pD3D9 = pD3D;
}

CIDirect3DDevice9::~CIDirect3DDevice9(void)
{

}

HRESULT CIDirect3DDevice9::QueryInterface (REFIID riid, void** ppvObj)
{
	*ppvObj = NULL;
	HRESULT hRes = m_pIDirect3DDevice9->QueryInterface(riid, ppvObj); 
	if (hRes == NOERROR)
	{
		*ppvObj = this;
	}
	return hRes;
}

ULONG CIDirect3DDevice9::AddRef(void)
{
    return(m_pIDirect3DDevice9->AddRef());
}

ULONG CIDirect3DDevice9::Release(void)
{
	ULONG uCount = m_pIDirect3DDevice9->Release();
	if(uCount == 0)
		delete this;

	return uCount;
}

HRESULT CIDirect3DDevice9::TestCooperativeLevel(void)
{
    return(m_pIDirect3DDevice9->TestCooperativeLevel());
}

UINT CIDirect3DDevice9::GetAvailableTextureMem(void)
{
    return(m_pIDirect3DDevice9->GetAvailableTextureMem());
}

HRESULT CIDirect3DDevice9::EvictManagedResources(void)
{
    return(m_pIDirect3DDevice9->EvictManagedResources());
}

HRESULT CIDirect3DDevice9::GetDirect3D(IDirect3D9** ppD3D9)
{
    HRESULT hr = m_pIDirect3DDevice9->GetDirect3D(ppD3D9);
	if(SUCCEEDED(hr))
		*ppD3D9 = m_pD3D9;

	return hr;
}

HRESULT CIDirect3DDevice9::GetDeviceCaps(D3DCAPS9* pCaps)
{
    return(m_pIDirect3DDevice9->GetDeviceCaps(pCaps));
}

HRESULT CIDirect3DDevice9::GetDisplayMode(UINT iSwapChain,D3DDISPLAYMODE* pMode)
{
    return(m_pIDirect3DDevice9->GetDisplayMode(iSwapChain, pMode));
}

HRESULT CIDirect3DDevice9::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
    return(m_pIDirect3DDevice9->GetCreationParameters(pParameters));
}

HRESULT CIDirect3DDevice9::SetCursorProperties(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap)
{
    return(m_pIDirect3DDevice9->SetCursorProperties(XHotSpot,YHotSpot,pCursorBitmap));
}

void CIDirect3DDevice9::SetCursorPosition(int X,int Y,DWORD Flags)
{
	return(m_pIDirect3DDevice9->SetCursorPosition(X,Y,Flags));
}

BOOL CIDirect3DDevice9::ShowCursor(BOOL bShow)
{
    return(m_pIDirect3DDevice9->ShowCursor(bShow));
}

HRESULT CIDirect3DDevice9::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain)  
{
    return(m_pIDirect3DDevice9->CreateAdditionalSwapChain(pPresentationParameters,pSwapChain));
}

HRESULT CIDirect3DDevice9::GetSwapChain(UINT iSwapChain,IDirect3DSwapChain9** pSwapChain)
{
    return(m_pIDirect3DDevice9->GetSwapChain(iSwapChain,pSwapChain));
}

UINT CIDirect3DDevice9::GetNumberOfSwapChains(void)
{
    return(m_pIDirect3DDevice9->GetNumberOfSwapChains());
}

HRESULT CIDirect3DDevice9::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	// Notify the device lost to our classes
	if(pChatBox)
		pChatBox->OnLostDevice();

	if(pChatInput)
		pChatInput->OnLostDevice();

	if(pGame->GetGameGui())
		pGame->GetGameGui()->OnLostDevice();

	if(pGame->GetNameTags())
		pGame->GetNameTags()->OnLostDevice();

	// Thats when we need a windowed mode!
	/*pPresentationParameters->Windowed = 1;
	pPresentationParameters->Flags = 0;
	pPresentationParameters->FullScreen_RefreshRateInHz = 0;
	pPresentationParameters->PresentationInterval = 0;
	LONG_PTR style = GetWindowLongPtr(pPresentationParameters->hDeviceWindow, GWL_STYLE);
	SetWindowLongPtr(pPresentationParameters->hDeviceWindow, GWL_STYLE, style | WS_POPUPWINDOW | WS_CAPTION | WS_THICKFRAME);
	SetWindowPos(pPresentationParameters->hDeviceWindow, HWND_NOTOPMOST, 0, 0, 800, 800, SWP_SHOWWINDOW);*/

	// Reset the device
	HRESULT hRet = m_pIDirect3DDevice9->Reset(pPresentationParameters);

	// Make sure the device is reseted
	if(hRet == D3D_OK)
	{
		// Notify the device reset to our classes
		if(pChatBox)
			pChatBox->OnResetDevice(); 

		if(pChatInput)
			pChatInput->OnResetDevice();

		if(pGame->GetGameGui())
			pGame->GetGameGui()->OnResetDevice();

		if(pGame->GetNameTags())
			pGame->GetNameTags()->OnRestDevice();
	}
	return hRet;
}

HRESULT CIDirect3DDevice9::Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion)
{	
	HRESULT hres = m_pIDirect3DDevice9->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	return (hres);
}

HRESULT CIDirect3DDevice9::GetBackBuffer(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer)
{
    return(m_pIDirect3DDevice9->GetBackBuffer(iSwapChain,iBackBuffer,Type,ppBackBuffer));
}

HRESULT CIDirect3DDevice9::GetRasterStatus(UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus)
{
    return(m_pIDirect3DDevice9->GetRasterStatus(iSwapChain,pRasterStatus));
}

HRESULT CIDirect3DDevice9::SetDialogBoxMode(BOOL bEnableDialogs)
{
    return(m_pIDirect3DDevice9->SetDialogBoxMode(bEnableDialogs));
}

void CIDirect3DDevice9::SetGammaRamp(UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp)
{
    return(m_pIDirect3DDevice9->SetGammaRamp(iSwapChain,Flags,pRamp));
}

void CIDirect3DDevice9::GetGammaRamp(UINT iSwapChain,D3DGAMMARAMP* pRamp)
{
    return(m_pIDirect3DDevice9->GetGammaRamp(iSwapChain,pRamp));
}

HRESULT CIDirect3DDevice9::CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateTexture(Width,Height,Levels,Usage,Format,Pool,ppTexture,pSharedHandle));
}

HRESULT CIDirect3DDevice9::CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateVolumeTexture(Width,Height,Depth,Levels,Usage,Format,Pool,ppVolumeTexture,pSharedHandle));
}

HRESULT CIDirect3DDevice9::CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateCubeTexture(EdgeLength,Levels,Usage,Format,Pool,ppCubeTexture,pSharedHandle));
}

HRESULT CIDirect3DDevice9::CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle)
{
	return(m_pIDirect3DDevice9->CreateVertexBuffer(Length,Usage,FVF,Pool,ppVertexBuffer,pSharedHandle));
}

HRESULT CIDirect3DDevice9::CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateIndexBuffer(Length,Usage,Format,Pool,ppIndexBuffer,pSharedHandle));
}

HRESULT CIDirect3DDevice9::CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateRenderTarget(Width,Height,Format,MultiSample,MultisampleQuality,Lockable,ppSurface,pSharedHandle));
}

HRESULT CIDirect3DDevice9::CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateDepthStencilSurface(Width,Height,Format,MultiSample,MultisampleQuality,Discard,ppSurface,pSharedHandle));
}

HRESULT CIDirect3DDevice9::UpdateSurface(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint)
{
    return(m_pIDirect3DDevice9->UpdateSurface(pSourceSurface,pSourceRect,pDestinationSurface,pDestPoint));
}

HRESULT CIDirect3DDevice9::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture)
{
    return(m_pIDirect3DDevice9->UpdateTexture(pSourceTexture,pDestinationTexture));
}

HRESULT CIDirect3DDevice9::GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface)
{
    return(m_pIDirect3DDevice9->GetRenderTargetData(pRenderTarget,pDestSurface));
}

HRESULT CIDirect3DDevice9::GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface)
{
    return(m_pIDirect3DDevice9->GetFrontBufferData(iSwapChain,pDestSurface));
}

HRESULT CIDirect3DDevice9::StretchRect(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter)
{
    return(m_pIDirect3DDevice9->StretchRect(pSourceSurface,pSourceRect,pDestSurface,pDestRect,Filter));
}

HRESULT CIDirect3DDevice9::ColorFill(IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color)
{
    return(m_pIDirect3DDevice9->ColorFill(pSurface,pRect,color));
}

HRESULT CIDirect3DDevice9::CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateOffscreenPlainSurface(Width,Height,Format,Pool,ppSurface,pSharedHandle));
}

HRESULT CIDirect3DDevice9::SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget)
{
    return(m_pIDirect3DDevice9->SetRenderTarget(RenderTargetIndex,pRenderTarget));
}

HRESULT CIDirect3DDevice9::GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget)
{
    return(m_pIDirect3DDevice9->GetRenderTarget(RenderTargetIndex,ppRenderTarget));
}

HRESULT CIDirect3DDevice9::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
    return(m_pIDirect3DDevice9->SetDepthStencilSurface(pNewZStencil));
}

HRESULT CIDirect3DDevice9::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
    return(m_pIDirect3DDevice9->GetDepthStencilSurface(ppZStencilSurface));
}

HRESULT CIDirect3DDevice9::BeginScene(void)
{
	return(m_pIDirect3DDevice9->BeginScene());
}

HRESULT CIDirect3DDevice9::EndScene(void)
{
	// Render our chatbox
	if(pChatBox)
		pChatBox->Render();

	// Render our chatinput
	if(pChatInput)
		pChatInput->Render();

	/// Render the GUI
	if(pGame->GetGameGui())
		pGame->GetGameGui()->Render();

	// Render the nametags
	if(pGame->GetNameTags())
		pGame->GetNameTags()->Render();

	return(m_pIDirect3DDevice9->EndScene());
}

HRESULT CIDirect3DDevice9::Clear(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil)
{
    return(m_pIDirect3DDevice9->Clear(Count,pRects,Flags,Color,Z,Stencil));
}

HRESULT CIDirect3DDevice9::SetTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix)
{
	if(pGame->GetNameTags())
	{
		if(State == D3DTS_VIEW)
			pGame->GetNameTags()->SetView(*pMatrix);
		else if(State == D3DTS_PROJECTION)
			pGame->GetNameTags()->SetProjection(*pMatrix);
	}
	return(m_pIDirect3DDevice9->SetTransform(State,pMatrix));
}

HRESULT CIDirect3DDevice9::GetTransform(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix)
{
    return(m_pIDirect3DDevice9->GetTransform(State,pMatrix));
}

HRESULT CIDirect3DDevice9::MultiplyTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix)
{
    return(m_pIDirect3DDevice9->MultiplyTransform(State,pMatrix));
}

HRESULT CIDirect3DDevice9::SetViewport(CONST D3DVIEWPORT9* pViewport)
{
    return(m_pIDirect3DDevice9->SetViewport(pViewport));
}

HRESULT CIDirect3DDevice9::GetViewport(D3DVIEWPORT9* pViewport)
{
    return(m_pIDirect3DDevice9->GetViewport(pViewport));
}

HRESULT CIDirect3DDevice9::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
    return(m_pIDirect3DDevice9->SetMaterial(pMaterial));
}

HRESULT CIDirect3DDevice9::GetMaterial(D3DMATERIAL9* pMaterial)
{
    return(m_pIDirect3DDevice9->GetMaterial(pMaterial));
}

HRESULT CIDirect3DDevice9::SetLight(DWORD Index,CONST D3DLIGHT9* pLight)
{
    return(m_pIDirect3DDevice9->SetLight(Index,pLight));
}

HRESULT CIDirect3DDevice9::GetLight(DWORD Index,D3DLIGHT9* pLight)
{
    return(m_pIDirect3DDevice9->GetLight(Index,pLight));
}

HRESULT CIDirect3DDevice9::LightEnable(DWORD Index,BOOL Enable)
{
    return(m_pIDirect3DDevice9->LightEnable(Index,Enable));
}

HRESULT CIDirect3DDevice9::GetLightEnable(DWORD Index,BOOL* pEnable)
{
    return(m_pIDirect3DDevice9->GetLightEnable(Index, pEnable));
}

HRESULT CIDirect3DDevice9::SetClipPlane(DWORD Index,CONST float* pPlane)
{
    return(m_pIDirect3DDevice9->SetClipPlane(Index, pPlane));
}

HRESULT CIDirect3DDevice9::GetClipPlane(DWORD Index,float* pPlane)
{
    return(m_pIDirect3DDevice9->GetClipPlane(Index,pPlane));
}

HRESULT CIDirect3DDevice9::SetRenderState(D3DRENDERSTATETYPE State,DWORD Value)
{
    return(m_pIDirect3DDevice9->SetRenderState(State, Value));
}

HRESULT CIDirect3DDevice9::GetRenderState(D3DRENDERSTATETYPE State,DWORD* pValue)
{
    return(m_pIDirect3DDevice9->GetRenderState(State, pValue));
}

HRESULT CIDirect3DDevice9::CreateStateBlock(D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB)
{
    return(m_pIDirect3DDevice9->CreateStateBlock(Type,ppSB));
}

HRESULT CIDirect3DDevice9::BeginStateBlock(void)
{
    return(m_pIDirect3DDevice9->BeginStateBlock());
}

HRESULT CIDirect3DDevice9::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
    return(m_pIDirect3DDevice9->EndStateBlock(ppSB));
}

HRESULT CIDirect3DDevice9::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus)
{
    return(m_pIDirect3DDevice9->SetClipStatus(pClipStatus));
}

HRESULT CIDirect3DDevice9::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
    return(m_pIDirect3DDevice9->GetClipStatus( pClipStatus));
}

HRESULT CIDirect3DDevice9::GetTexture(DWORD Stage,IDirect3DBaseTexture9** ppTexture)
{
    return(m_pIDirect3DDevice9->GetTexture(Stage,ppTexture));
}

HRESULT CIDirect3DDevice9::SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture)
{
    return(m_pIDirect3DDevice9->SetTexture(Stage,pTexture));
}

HRESULT CIDirect3DDevice9::GetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue)
{
    return(m_pIDirect3DDevice9->GetTextureStageState(Stage,Type, pValue));
}

HRESULT CIDirect3DDevice9::SetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value)
{
    return(m_pIDirect3DDevice9->SetTextureStageState(Stage,Type,Value));
}

HRESULT CIDirect3DDevice9::GetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue)
{
    return(m_pIDirect3DDevice9->GetSamplerState(Sampler,Type, pValue));
}

HRESULT CIDirect3DDevice9::SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value)
{
    return(m_pIDirect3DDevice9->SetSamplerState(Sampler,Type,Value));
}

HRESULT CIDirect3DDevice9::ValidateDevice(DWORD* pNumPasses)
{
    return(m_pIDirect3DDevice9->ValidateDevice( pNumPasses));
}

HRESULT CIDirect3DDevice9::SetPaletteEntries(UINT PaletteNumber,CONST PALETTEENTRY* pEntries)
{
    return(m_pIDirect3DDevice9->SetPaletteEntries(PaletteNumber, pEntries));
}

HRESULT CIDirect3DDevice9::GetPaletteEntries(UINT PaletteNumber,PALETTEENTRY* pEntries)
{
    return(m_pIDirect3DDevice9->GetPaletteEntries(PaletteNumber, pEntries));
}

HRESULT CIDirect3DDevice9::SetCurrentTexturePalette(UINT PaletteNumber)
{
    return(m_pIDirect3DDevice9->SetCurrentTexturePalette(PaletteNumber));
}

HRESULT CIDirect3DDevice9::GetCurrentTexturePalette(UINT *PaletteNumber)
{
    return(m_pIDirect3DDevice9->GetCurrentTexturePalette(PaletteNumber));
}

HRESULT CIDirect3DDevice9::SetScissorRect(CONST RECT* pRect)
{
    return(m_pIDirect3DDevice9->SetScissorRect( pRect));
}

HRESULT CIDirect3DDevice9::GetScissorRect( RECT* pRect)
{
    return(m_pIDirect3DDevice9->GetScissorRect( pRect));
}

HRESULT CIDirect3DDevice9::SetSoftwareVertexProcessing(BOOL bSoftware)
{
    return(m_pIDirect3DDevice9->SetSoftwareVertexProcessing(bSoftware));
}

BOOL    CIDirect3DDevice9::GetSoftwareVertexProcessing(void)
{
    return(m_pIDirect3DDevice9->GetSoftwareVertexProcessing());
}

HRESULT CIDirect3DDevice9::SetNPatchMode(float nSegments)
{
    return(m_pIDirect3DDevice9->SetNPatchMode(nSegments));
}

float   CIDirect3DDevice9::GetNPatchMode(void)
{
    return(m_pIDirect3DDevice9->GetNPatchMode());
}

HRESULT CIDirect3DDevice9::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount)
{
    return(m_pIDirect3DDevice9->DrawPrimitive(PrimitiveType,StartVertex,PrimitiveCount));
}

HRESULT CIDirect3DDevice9::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
    return(m_pIDirect3DDevice9->DrawIndexedPrimitive(PrimitiveType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount));
}

HRESULT CIDirect3DDevice9::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
    return(m_pIDirect3DDevice9->DrawPrimitiveUP(PrimitiveType,PrimitiveCount,pVertexStreamZeroData,VertexStreamZeroStride));
}

HRESULT CIDirect3DDevice9::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
    return(m_pIDirect3DDevice9->DrawIndexedPrimitiveUP(PrimitiveType,MinVertexIndex,NumVertices,PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData,VertexStreamZeroStride));
}

HRESULT CIDirect3DDevice9::ProcessVertices(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags)
{
    return(m_pIDirect3DDevice9->ProcessVertices( SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags));
}

HRESULT CIDirect3DDevice9::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl)
{
    return(m_pIDirect3DDevice9->CreateVertexDeclaration( pVertexElements,ppDecl));
}

HRESULT CIDirect3DDevice9::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
    return(m_pIDirect3DDevice9->SetVertexDeclaration(pDecl));
}

HRESULT CIDirect3DDevice9::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
    return(m_pIDirect3DDevice9->GetVertexDeclaration(ppDecl));
}

HRESULT CIDirect3DDevice9::SetFVF(DWORD FVF)
{
    return(m_pIDirect3DDevice9->SetFVF(FVF));
}

HRESULT CIDirect3DDevice9::GetFVF(DWORD* pFVF)
{
    return(m_pIDirect3DDevice9->GetFVF(pFVF));
}

HRESULT CIDirect3DDevice9::CreateVertexShader(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader)
{
    return(m_pIDirect3DDevice9->CreateVertexShader(pFunction,ppShader));
}

HRESULT CIDirect3DDevice9::SetVertexShader(IDirect3DVertexShader9* pShader)
{
    return(m_pIDirect3DDevice9->SetVertexShader(pShader));
}

HRESULT CIDirect3DDevice9::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
    return(m_pIDirect3DDevice9->GetVertexShader(ppShader));
}

HRESULT CIDirect3DDevice9::SetVertexShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
{
    return(m_pIDirect3DDevice9->SetVertexShaderConstantF(StartRegister,pConstantData, Vector4fCount));
}

HRESULT CIDirect3DDevice9::GetVertexShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount)
{
    return(m_pIDirect3DDevice9->GetVertexShaderConstantF(StartRegister,pConstantData,Vector4fCount));
}

HRESULT CIDirect3DDevice9::SetVertexShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)
{
    return(m_pIDirect3DDevice9->SetVertexShaderConstantI(StartRegister,pConstantData,Vector4iCount));
}

HRESULT CIDirect3DDevice9::GetVertexShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount)
{
    return(m_pIDirect3DDevice9->GetVertexShaderConstantI(StartRegister,pConstantData,Vector4iCount));
}

HRESULT CIDirect3DDevice9::SetVertexShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
{
    return(m_pIDirect3DDevice9->SetVertexShaderConstantB(StartRegister,pConstantData,BoolCount));
}

HRESULT CIDirect3DDevice9::GetVertexShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
{
    return(m_pIDirect3DDevice9->GetVertexShaderConstantB(StartRegister,pConstantData,BoolCount));
}

HRESULT CIDirect3DDevice9::SetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride)
{
    return(m_pIDirect3DDevice9->SetStreamSource(StreamNumber,pStreamData,OffsetInBytes,Stride));
}

HRESULT CIDirect3DDevice9::GetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* OffsetInBytes,UINT* pStride)
{
    return(m_pIDirect3DDevice9->GetStreamSource(StreamNumber,ppStreamData,OffsetInBytes,pStride));
}

HRESULT CIDirect3DDevice9::SetStreamSourceFreq(UINT StreamNumber,UINT Divider)
{
    return(m_pIDirect3DDevice9->SetStreamSourceFreq(StreamNumber,Divider));
}

HRESULT CIDirect3DDevice9::GetStreamSourceFreq(UINT StreamNumber,UINT* Divider)
{
    return(m_pIDirect3DDevice9->GetStreamSourceFreq(StreamNumber,Divider));
}

HRESULT CIDirect3DDevice9::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
    return(m_pIDirect3DDevice9->SetIndices(pIndexData));
}

HRESULT CIDirect3DDevice9::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
    return(m_pIDirect3DDevice9->GetIndices(ppIndexData));
}

HRESULT CIDirect3DDevice9::CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader)
{
    return(m_pIDirect3DDevice9->CreatePixelShader(pFunction,ppShader));
}

HRESULT CIDirect3DDevice9::SetPixelShader(IDirect3DPixelShader9* pShader)
{
    return(m_pIDirect3DDevice9->SetPixelShader(pShader));
}

HRESULT CIDirect3DDevice9::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
    return(m_pIDirect3DDevice9->GetPixelShader(ppShader));
}

HRESULT CIDirect3DDevice9::SetPixelShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
{
    return(m_pIDirect3DDevice9->SetPixelShaderConstantF(StartRegister,pConstantData,Vector4fCount));
}

HRESULT CIDirect3DDevice9::GetPixelShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount)
{
    return(m_pIDirect3DDevice9->GetPixelShaderConstantF(StartRegister,pConstantData,Vector4fCount));
}

HRESULT CIDirect3DDevice9::SetPixelShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)
{
    return(m_pIDirect3DDevice9->SetPixelShaderConstantI(StartRegister,pConstantData,Vector4iCount));
}

HRESULT CIDirect3DDevice9::GetPixelShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount)
{
    return(m_pIDirect3DDevice9->GetPixelShaderConstantI(StartRegister,pConstantData,Vector4iCount));
}

HRESULT CIDirect3DDevice9::SetPixelShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
{
    return(m_pIDirect3DDevice9->SetPixelShaderConstantB(StartRegister,pConstantData,BoolCount));
}

HRESULT CIDirect3DDevice9::GetPixelShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
{
    return(m_pIDirect3DDevice9->GetPixelShaderConstantB(StartRegister,pConstantData,BoolCount));
}

HRESULT CIDirect3DDevice9::DrawRectPatch(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
    return(m_pIDirect3DDevice9->DrawRectPatch(Handle,pNumSegs, pRectPatchInfo));
}

HRESULT CIDirect3DDevice9::DrawTriPatch(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
    return(m_pIDirect3DDevice9->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo));
}

HRESULT CIDirect3DDevice9::DeletePatch(UINT Handle)
{
    return(m_pIDirect3DDevice9->DeletePatch(Handle));
}

HRESULT CIDirect3DDevice9::CreateQuery(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery)
{
    return(m_pIDirect3DDevice9->CreateQuery(Type,ppQuery));
}

