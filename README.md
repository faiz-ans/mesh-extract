
# Maya Plugin for Mesh Data Storage and Manipulation

## Project Name
Mesh Data Store and Proxy Generator Plugin for Autodesk Maya

## Overview
This project is a C++ plugin for Autodesk Maya that allows users to extract, store, and manipulate mesh data, including vertices, faces, normals, and UVs, within a defined volume in a scene. The plugin integrates seamlessly with Maya's API, providing automation and functionality for analyzing and generating meshes.

## Key Features
1. **Mesh Data Extraction**:
   - Captures vertices, faces, normals, and UVs of all meshes within a specified spherical volume in a scene.
   - Provides detailed information about the geometry for analysis or further manipulation.

2. **Data Storage**:
   - Uses a custom-built data structure (`MeshInfoStore`) to store mesh information efficiently.
   - Supports multiple meshes and keeps each mesh's data distinct.

3. **Mesh Manipulation**:
   - Generates new meshes in Maya from stored data.
   - Automates polygon reduction to create proxy meshes optimized for real-time applications.

4. **Integration with Maya**:
   - Utilizes Maya's C++ API for scene interaction.
   - Commands integrated into Maya’s interface for ease of use.

## How It Works
1. **Selection Area**:
   - The plugin defines a spherical volume in the scene using a center point and radius.
   - Automatically selects all meshes that fall within the defined area.

2. **Data Processing**:
   - Extracts geometric data (vertices, faces, normals, and UVs) from the selected meshes.
   - Stores the data in `MeshInfoStore` objects for further operations.

3. **Output**:
   - Displays extracted mesh data directly in Maya's script editor.
   - Generates new meshes or proxy meshes using stored data and applies polygon reduction.

## Installation
1. Clone the repository or download the plugin source code.
2. Open the provided Visual Studio project file (`polyreduce-env.vcxproj`) and build the project.
3. Copy the compiled `.mll` file to your Maya plugins folder.
4. Load the plugin in Maya using the Plugin Manager.

## Usage
1. Load the plugin in Maya.
2. Run the following command in Maya's script editor to execute the plugin:
   ```mel
   meshInfoStore
   ```
   This will:
   - Extract mesh data from the defined volume.
   - Display information about the extracted meshes in the script editor.
   - Generate proxy meshes with polygon reduction.

3. Customize the spherical volume parameters (`centerPoint`, `radiusPoint`) in the `doIt` method of `MeshInfoStoreCmd.cpp` to adjust the selection area.

## Technical Highlights
- **C++ Integration**: Built using Autodesk Maya’s C++ API to ensure efficient interaction with scene geometry.
- **Custom Data Structures**:
  - `Vertex` and `Face` classes for representing mesh components.
  - `MeshInfoStore` class for storing and retrieving mesh data.
- **Automation**:
  - Proxy generation and polygon reduction integrated via MEL commands.

## Future Enhancements
- Add support for dynamic user input to define selection areas.
- Extend functionality for exporting and importing mesh data.
- Include more advanced mesh processing options.

## Author
Faiz Ansari  
Version: 1.0
