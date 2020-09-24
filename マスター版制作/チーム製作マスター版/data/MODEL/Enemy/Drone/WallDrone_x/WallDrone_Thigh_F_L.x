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
 14.58400;-14.01099;-21.81685;,
 19.20330;-11.93989;-16.07655;,
 -3.90060;-0.75509;8.77495;,
 -9.01760;-2.08479;3.24075;,
 24.94360;-6.93989;-15.28405;,
 3.04100;2.45511;9.06985;,
 28.44220;-1.93989;-19.90335;,
 7.74100;5.66531;3.95285;,
 27.64949;0.13111;-27.22875;,
 7.44610;6.99500;-3.57865;,
 23.03019;-1.93989;-32.96906;,
 2.32899;5.66531;-9.11285;,
 17.28990;-6.93989;-33.76165;,
 -4.61260;2.45511;-9.40775;,
 13.79139;-11.93989;-29.14225;,
 -9.31250;-0.75509;-4.29065;,
 14.58400;-14.01099;-21.81685;,
 -9.01760;-2.08479;3.24075;,
 -9.01760;-2.08479;3.24075;,
 -3.90060;-0.75509;8.77495;,
 -9.01760;-2.08479;3.24075;,
 2.32899;5.66531;-9.11285;,
 3.04100;2.45511;9.06985;,
 7.74100;5.66531;3.95285;;
 
 11;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;11,18,19,9;,
 4;15,20,21,13;,
 4;19,22,23,9;;
 
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
  -0.343089;-0.932731;0.110921;,
  0.156064;-0.842174;0.516126;,
  0.617404;-0.354927;0.702025;,
  0.752689;0.023076;0.657972;,
  0.260467;0.963004;-0.069142;,
  -0.206601;0.862053;-0.462797;,
  -0.626232;0.359253;-0.691933;,
  -0.741778;-0.487008;-0.461073;,
  -0.096161;0.993556;0.059999;,
  -0.334688;0.930895;-0.146348;,
  0.489090;0.857484;0.159724;,
  0.039103;0.981545;0.187190;,
  -0.419433;0.891007;0.173734;,
  -0.419432;0.891007;0.173733;,
  -0.419434;0.891006;0.173734;,
  -0.419433;0.891007;0.173731;;
  11;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;10,4,8,11;,
  4;4,5,9,8;,
  4;5,6,6,9;,
  4;6,7,7,6;,
  4;7,0,0,7;,
  4;9,12,13,8;,
  4;14,12,9,14;,
  4;13,15,11,8;;
 }
 MeshTextureCoords {
  24;
  0.375000;0.000000;,
  0.375000;0.125000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.625000;,
  0.500000;0.500000;,
  0.500000;0.875000;,
  0.500000;0.750000;,
  0.500000;0.500000;,
  0.500000;0.500000;;
 }
}
