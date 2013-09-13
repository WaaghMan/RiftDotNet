#pragma once

#include <OVR_Device.h>
#include <OVR_DeviceImpl.h>

#include "RiftDotNet.h"
#include "System.h"
#include "DeviceBase.h"
#include "DeviceHandle.h"
#include "DeviceEnumerable.h"
#include "HMDDevice.h"
#include "SensorDevice.h"
#include "ValueWrapper.h"

using namespace System::Collections::Generic;



namespace RiftDotNet
{
	namespace Platform
	{
		public ref class DeviceManager
			: public DeviceBase
			, public IDeviceManager
		{
		private:

		public:

			static DeviceManager^ Create()
			{
				auto native = OVR::DeviceManager::Create();
				return gcnew DeviceManager(native);
			}

			DeviceManager(OVR::DeviceManager* native)
				: DeviceBase(native)
			{}

			~DeviceManager()
			{
				
			}

			property RiftDotNet::IDeviceInfo^ Info
			{
				virtual RiftDotNet::IDeviceInfo^ get() override
				{
					if (IsDisposed)
						throw gcnew ObjectDisposedException("IHMDDevice");

					OVR::DeviceInfo info;
					GetNative<OVR::DeviceManager>()->GetDeviceInfo(&info);
					return gcnew RiftDotNet::Platform::DeviceInfo(info);
				}
			}

			/// The enumeration of all sensor devices
			property DisposableArray<IDeviceHandle<ISensorDevice^, ISensorInfo^>^>^ SensorDevices
			{
				virtual DisposableArray<IDeviceHandle<ISensorDevice^, ISensorInfo^>^>^ get()
				{
					if (IsDisposed)
						throw gcnew ObjectDisposedException("IDeviceHandle");

					auto enumerator = GetNative<OVR::DeviceManager>()->EnumerateDevices<OVR::SensorDevice>(true);
					auto ret = gcnew List<IDeviceHandle<ISensorDevice^, ISensorInfo^>^>();

					while(enumerator.GetType() != OVR::Device_None)
					{
						auto wrapper = new EnumeratorWrapper<OVR::DeviceEnumerator<OVR::SensorDevice>>(enumerator);
						ret->Add(gcnew TypedDeviceHandle<ISensorDevice^,ISensorInfo^>(wrapper));

						if (!enumerator.Next())
							break;
					}

					return gcnew DisposableArray<IDeviceHandle<ISensorDevice^, ISensorInfo^>^>(ret->ToArray());
				}
			}

			/// The enumeration of all HMD devices.
			property DisposableArray<IDeviceHandle<IHMDDevice^, IHMDInfo^>^>^ HMDDevices
			{
				virtual DisposableArray<IDeviceHandle<IHMDDevice^, IHMDInfo^>^>^ get()
				{
					if (IsDisposed)
						throw gcnew ObjectDisposedException("IDeviceHandle");

					auto enumerator = GetNative<OVR::DeviceManager>()->EnumerateDevices<OVR::HMDDevice>(true);
					auto ret = gcnew List<IDeviceHandle<IHMDDevice^,IHMDInfo^>^>();

					while(enumerator.GetType() != OVR::Device_None)
					{
						auto wrapper = new EnumeratorWrapper<OVR::DeviceEnumerator<OVR::HMDDevice>>(enumerator);
						ret->Add(gcnew TypedDeviceHandle<IHMDDevice^,IHMDInfo^>(wrapper));

						if (!enumerator.Next())
							break;
					}

					return gcnew DisposableArray<IDeviceHandle<IHMDDevice^, IHMDInfo^>^>(ret->ToArray());
				}
			}

		private:
		};
	}
}