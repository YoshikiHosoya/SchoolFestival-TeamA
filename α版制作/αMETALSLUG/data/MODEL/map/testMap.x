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
 22;
 -385.34174;0.00000;100.00000;,
 -385.34174;0.00000;-100.00000;,
 -602.25769;0.00000;-100.00000;,
 -602.25769;0.00000;100.00000;,
 -287.66461;-165.29977;100.00000;,
 -287.66461;-165.29977;-100.00000;,
 -386.41510;-165.29977;-100.00000;,
 -386.41510;-165.29977;100.00000;,
 325.23270;0.00000;100.00000;,
 325.23270;0.00000;-100.00000;,
 171.74005;0.00000;-100.00000;,
 171.74005;0.00000;100.00000;,
 364.27438;107.33753;100.00000;,
 602.25769;107.33753;100.00000;,
 602.25769;107.33753;-100.00000;,
 364.27438;107.33753;-100.00000;,
 9.66659;83.58104;100.00000;,
 9.66659;83.58104;-100.00000;,
 -282.29761;-0.21064;-100.00000;,
 -282.29761;-0.21064;100.00000;,
 122.36478;83.64945;100.00000;,
 122.36478;83.64945;-100.00000;;
 
 8;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,15,9,8;,
 4;16,17,18,19;,
 4;20,11,10,21;,
 4;20,21,17,16;;
 
 MeshMaterialList {
  6;
  8;
  4,
  5,
  4,
  4,
  2,
  0,
  1,
  4;;
  Material {
   0.034510;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.746667;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.097255;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.050196;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.577255;0.580392;0.558431;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  6;
  0.000000;1.000000;0.000000;,
  0.495824;0.868423;0.000000;,
  -0.275857;0.961199;0.000000;,
  -0.139587;0.990210;0.000000;,
  0.495560;0.868574;0.000000;,
  -0.939766;0.341819;0.000000;;
  8;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,1,1;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;3,3,2,2;,
  4;4,1,1,4;,
  4;4,4,3,3;;
 }
 MeshTextureCoords {
  22;
  0.180086;0.000000;,
  0.180086;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.442077;0.000000;,
  0.442077;1.000000;,
  0.326230;1.000000;,
  0.326230;0.000000;,
  0.770011;0.000000;,
  0.770011;1.000000;,
  0.642580;1.000000;,
  0.642580;0.000000;,
  0.892095;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.892095;1.000000;,
  0.568563;0.000000;,
  0.568563;1.000000;,
  0.532959;1.000000;,
  0.532959;0.000000;,
  0.604166;0.000000;,
  0.604166;1.000000;;
 }
}
