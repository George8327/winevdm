# winevdm on 64-bit Windows

![screenshot](screenshot.PNG)

[Download stable version](https://github.com/otya128/winevdm/releases)

[Download latest version (unstable)](https://ci.appveyor.com/project/otya128/winevdm/)

16-bit Windows (Windows 1.x, 2.x, 3.0, 3.1, etc.) on 64-bit Windows

An altered version of winevdm (a 16-bit Windows emulator), ported to 64-bit Windows.

# How to compile(Visual Studio)

+ Install Visual Studio 2017
+ Edit PropertySheet.props
+ Compile

# How to compile(cmake)

```sh
git clone https://github.com/otya128/winevdm.git
cd winevdm
mkdir build
cd build
cmake ..
make
```

# How to run

+ If you get an error that VCRUNTIME140.dll is missing, install [Microsoft Visual C++ Redistributable for Visual Studio 2017 (32-bit)](https://aka.ms/vs/15/release/vc_redist.x86.exe)
+ Drag and drop Win16 executable file to otvdm.exe or execute otvdmw.exe.

# How to install

+ Download or compile
+ Edit install.inf
+ Right-click on install.inf and select "Install"
+ You can execute Win16 binaries directly!

**If you install v0.4.x, you should replace [Strings] section of install.inf with these and install install.inf again.**
```ini
[Strings]
NtVdm64=SOFTWARE\Microsoft\Windows NT\CurrentVersion\NtVdm64
CommandLine="""%m"" %c"
MappedExeName=otvdm.exe
```

# How does it work?

This program contains the following items

+ CPU Emulator
  + 64-bit Windows cannot modify LDT(NtSetInformationProcess(,ProcessLdtInformation,,) always returns error)
+ wine based Win16->Win32 conversion codes:
```c
BOOL16 WINAPI DestroyWindow16( HWND16 hwnd )
{
    return DestroyWindow( WIN_Handle32(hwnd) );
}
```
Relay routines from 16-bit to 32-bit are autogenerated by convspec
```spec
53  pascal -ret16 DestroyWindow(word) DestroyWindow16
```
+ DOS emulation for Win16
+ 16-bit <=> native HANDLE conversion
+ Fix compatibility problems, fix compatibility problems

## install.inf

When 64-bit Windows detects a 16-bit installer, it has a mechanism to start an alternative installer which is not 16-bit.
This program uses it.

## WINDOWS directory redirection

Some Win16 programs try to save their settings in %WINDIR%\<filename>.ini

In recent Windows, it is not allowed to save to %WINDIR%, so it redirects.

# winevdm
```bat
winevdm.exe [--app-name app.exe] command line
winevdm.exe CALC.EXE
```
It can also run DOS executables (DOS emulator-like).
You can set the DOS version with the VDMDOSVER environment variable.

