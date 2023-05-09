# Install libs

Follow steps below to install all packages.

## Visual Studio Integration

Run the command below as administrator.

```powershell
vcpkg integrate install
```

Turn off the integration by running:

```powershell
vcpkg integrate remove
```

---

Run each line in your terminal to install all packages.

### assimp

```powershell
vcpkg install assimp:x64-windows && vcpkg install assimp:x86-windows
```

### glfw

```powershell
vcpkg install glfw3:x64-windows && vcpkg install glfw3:x86-windows
```

### glad

```powershell
vcpkg install glad:x64-windows && vcpkg install glad:x86-windows
```

<!--
### freeglut

```powershell
vcpkg install freeglut:x64-windows && vcpkg install freeglut:x86-windows
```

### glew

```powershell
vcpkg install glew:x64-windows && vcpkg install glew:x86-windows
```
-->

### glm

```powershell
vcpkg install glm:x64-windows && vcpkg install glm:x86-windows
```

### opengl

```powershell
vcpkg install opengl:x64-windows && vcpkg install opengl:x86-windows
```

### opengl-registry

```powershell
vcpkg install opengl-registry:x64-windows && vcpkg install opengl-registry:x86-windows
```
