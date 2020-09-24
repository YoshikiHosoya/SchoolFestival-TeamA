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
 24;
 16.02104;-16.29756;21.53786;,
 -7.58056;-4.37136;-3.51974;,
 -2.46356;-3.04166;-9.05394;,
 20.64034;-14.22646;15.79756;,
 4.47804;0.16854;-9.34884;,
 26.38065;-9.22646;15.00506;,
 9.17805;3.37874;-4.23184;,
 29.87924;-4.22646;19.62436;,
 8.88315;4.70844;3.29966;,
 29.08654;-2.15546;26.94976;,
 3.76604;3.37874;8.83386;,
 24.46724;-4.22646;32.69006;,
 -3.17555;0.16854;9.12876;,
 18.72695;-9.22646;33.48266;,
 -7.87546;-3.04166;4.01166;,
 15.22844;-14.22646;28.86325;,
 -7.58056;-4.37136;-3.51974;,
 16.02104;-16.29756;21.53786;,
 -2.46356;-3.04166;-9.05394;,
 -7.58056;-4.37136;-3.51974;,
 3.76604;3.37874;8.83386;,
 -7.58056;-4.37136;-3.51974;,
 9.17805;3.37874;-4.23184;,
 4.47804;0.16854;-9.34884;;
 
 11;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;10,8,18,19;,
 4;14,12,20,21;,
 4;18,8,22,23;;
 
 MeshMaterialList {
  1;
  11;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.276570;0.000000;0.630000;1.000000;;
   21.000000;
   0.340000;0.340000;0.340000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  16;
  -0.343089;-0.932731;-0.110921;,
  0.156064;-0.842174;-0.516126;,
  0.617404;-0.354927;-0.702025;,
  0.752689;0.023076;-0.657972;,
  0.260467;0.963004;0.069142;,
  -0.206601;0.862053;0.462797;,
  -0.626232;0.359253;0.691933;,
  -0.741778;-0.487008;0.461073;,
  -0.096161;0.993556;-0.059999;,
  -0.334688;0.930895;0.146348;,
  0.489090;0.857484;-0.159724;,
  0.039103;0.981545;-0.187191;,
  -0.419432;0.891007;-0.173733;,
  -0.419433;0.891007;-0.173734;,
  -0.419434;0.891006;-0.173734;,
  -0.419433;0.891007;-0.173731;;
  11;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;10,11,8,4;,
  4;4,8,9,5;,
  4;5,9,6,6;,
  4;6,6,7,7;,
  4;7,7,0,0;,
  4;9,8,12,13;,
  4;14,14,9,13;,
  4;12,8,11,15;;
 }
 MeshTextureCoords {
  24;
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.375000;0.125000;,
  0.500000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.875000;,
  0.375000;0.875000;,
  0.500000;1.000000;,
  0.375000;1.000000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.500000;0.500000;,
  0.500000;0.500000;;
 }
}
