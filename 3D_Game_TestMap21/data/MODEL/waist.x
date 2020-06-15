xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 46;
 -5.01626;0.01290;-0.00555;,
 -4.13303;0.01290;-3.28007;,
 -5.37846;-5.17188;-3.82759;,
 -6.52893;-5.17188;-0.00555;,
 4.09930;0.01290;-3.28007;,
 5.34474;-5.17188;-3.82760;,
 4.98252;0.01290;-0.00555;,
 6.49520;-5.17188;-0.00555;,
 4.09929;0.01290;3.26897;,
 5.34473;-5.17188;3.81649;,
 -4.13303;0.01290;3.26897;,
 -5.37846;-5.17188;3.81650;,
 -5.01626;0.01290;-0.00555;,
 -6.52893;-5.17188;-0.00555;,
 -0.01686;0.01290;-0.00556;,
 -0.01686;0.01290;-0.00556;,
 -0.01686;0.01290;-0.00556;,
 -0.01686;0.01290;-0.00556;,
 -0.01686;0.01290;-0.00556;,
 -0.01686;0.01290;-0.00556;,
 -0.01686;-5.17188;-0.00556;,
 -0.01686;-5.17188;-0.00556;,
 -0.01686;-5.17188;-0.00556;,
 -0.01686;-5.17188;-0.00556;,
 -0.01686;-5.17188;-0.00556;,
 -0.01686;-5.17188;-0.00556;,
 -3.95469;3.44391;-3.06650;,
 3.95469;3.44391;-3.06650;,
 3.95469;-1.70673;-3.06650;,
 -3.95469;-1.70673;-3.06650;,
 3.95469;3.44391;-3.06650;,
 3.95469;3.44391;3.06650;,
 3.95469;-1.70673;3.06650;,
 3.95469;-1.70673;-3.06650;,
 3.95469;3.44391;3.06650;,
 -3.95469;3.44391;3.06650;,
 -3.95469;-1.70673;3.06650;,
 3.95469;-1.70673;3.06650;,
 -3.95469;3.44391;3.06650;,
 -3.95469;3.44391;-3.06650;,
 -3.95469;-1.70673;-3.06650;,
 -3.95469;-1.70673;3.06650;,
 3.95469;3.44391;-3.06650;,
 -3.95469;3.44391;-3.06650;,
 -3.95469;-1.70673;-3.06650;,
 3.95469;-1.70673;-3.06650;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 3;14,1,0;,
 3;15,4,1;,
 3;16,6,4;,
 3;17,8,6;,
 3;18,10,8;,
 3;19,12,10;,
 3;20,3,2;,
 3;21,2,5;,
 3;22,5,7;,
 3;23,7,9;,
 3;24,9,11;,
 3;25,11,13;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;38,31,42,43;,
 4;44,45,32,41;;
 
 MeshMaterialList {
  3;
  24;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.734400;0.401600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.200000;0.183600;0.100400;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.194400;0.081600;0.053600;1.000000;;
   5.000000;
   0.100000;0.100000;0.100000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  14;
  0.000000;1.000000;0.000000;,
  -0.962928;0.269760;-0.000000;,
  -0.928534;0.260125;-0.264878;,
  -0.000000;0.105018;-0.994470;,
  0.962927;0.269762;0.000001;,
  0.928533;0.260127;0.264878;,
  0.000000;0.105018;0.994470;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.928534;0.260127;-0.264875;,
  -0.928534;0.260125;0.264878;,
  -1.000000;0.000000;0.000000;;
  24;
  4;1,2,2,1;,
  4;3,3,3,3;,
  4;11,4,4,11;,
  4;4,5,5,4;,
  4;6,6,6,6;,
  4;12,1,1,12;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  3;7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;7,7,7,7;;
 }
 MeshTextureCoords {
  46;
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}