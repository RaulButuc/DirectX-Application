/**
 *  DirectXUtilities.h
 *  Purpose: Provide memory management tools for the main DirectX window.
 *
 *  @author Raul Butuc
 *  @version 1.0.0 07/03/2015
 */

#pragma once

#include <d3d11.h>
#include <DirectXColors.h>

#pragma comment(lib, "d3d11.lib")

namespace MemoryManagement {

	/**
	 *  Safely deallocate a pointer from memory after being used.
	 *
	 *  @param _ptr The pointer of generic type _PtrT that is to be deallocated.
	 */
	template <typename _PtrT>
	void SafeDelete(_PtrT& _ptr) {
		if (_ptr) {
			delete _ptr;
			_ptr = nullptr;
		}
	}

	/**
	 *  Safely deallocate an array from memory after being used.
	 *
	 *  @param _ptr The pointer of generic type _PtrT that is to be deallocated.
	 */
	template <typename _PtrT>
	void SafeDeleteArr(_PtrT& _ptr) {
		if (_ptr) {
			delete[] _ptr;
			_ptr = nullptr;
		}
	}

	/**
	 *  Safely release a pointer from memory after being used.
	 *
	 *  @param _ptr The pointer of generic type _PtrT that is to be released.
	 */
	template <typename _PtrT>
	void SafeRelease(_PtrT& _ptr) {
		if (_ptr) {
			_ptr->Release();
			_ptr = nullptr;
		}
	}
}