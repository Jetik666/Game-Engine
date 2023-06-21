#pragma once

// Graphics exception checking/throwing macros (some with dxgi infos)
#define GFX_EXCEPT_NOINFO(hr) Graphics::HrException(__LINE__, __FILE__, (hr))
#define GFX_THROW_NOINFO(hrcall) if(FAILED(hr = (hrcall))) throw Graphics::HrException(__LINE__, __FILE__, hr)

#ifndef NDEBUG
#define GFX_EXCEPT(hr) Graphics::HrException( __LINE__, __FILE__, (hr), pInfoManager.GetMessages())
#define GFX_THROW_INFO(hrcall) pInfoManager.Set(); if(FAILED(hr = (hrcall))) throw GFX_EXCEPT(hr)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException( __LINE__,__FILE__,(hr), pInfoManager.GetMessages() )
#define GFX_THROW_INFO_ONLY(call) pInfoManager.Set(); (call); {auto v = pInfoManager.GetMessages(); if(!v.empty()) {throw Graphics::InfoException( __LINE__,__FILE__,v);}}
#else
#define GFX_EXCEPT(hr) Graphics::HrException(__LINE__,__FILE__,(hr))
#define GFX_THROW_INFO(hrcall) GFX_THROW_NOINFO(hrcall)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException(__LINE__,__FILE__,(hr))
#define GFX_THROW_INFO_ONLY(call) (call)
#endif

// Macro for importing infomanager into local scope
// this.GetInfoManager(Graphics& gfx) must exist
#ifdef  NDEBUG
#define INFOMAN(gfx) HRESULT hr
#else
#define INFOMAN(gfx) HRESULT hr, DxgiInfoManager& infoManager = GetInfoManager((gfx))
#endif //  NDEBUG
