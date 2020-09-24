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
 -6.19624;-27.47583;-4.83341;,
 -0.78424;-27.47583;0.57849;,
 -3.14484;-2.79353;9.87369;,
 -7.76414;-4.86463;4.13339;,
 6.86946;-27.47583;0.57849;,
 2.59546;2.20647;10.66619;,
 12.28136;-27.47583;-4.83341;,
 6.09406;7.20647;6.04689;,
 12.28136;-27.47583;-12.48711;,
 5.30136;9.27747;-1.27851;,
 6.86936;-27.47583;-17.89911;,
 0.68206;7.20647;-7.01881;,
 -0.78424;-27.47583;-17.89911;,
 -5.05824;2.20647;-7.81141;,
 -6.19624;-27.47583;-12.48711;,
 -8.55674;-2.79353;-3.19201;,
 -6.19624;-27.47583;-4.83341;,
 -7.76414;-4.86463;4.13339;,
 6.86946;-27.47583;0.57849;,
 -0.78424;-27.47583;0.57849;,
 6.86946;-27.47583;0.57849;,
 6.86936;-27.47583;-17.89911;,
 -6.19624;-27.47583;-4.83341;,
 -6.19624;-27.47583;-12.48711;;
 
 11;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;10,18,19,12;,
 4;6,20,21,8;,
 4;19,22,23,12;;
 
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
  9;
  0.941350;0.055046;0.332912;,
  0.886340;0.277882;-0.370382;,
  -0.448741;0.236606;-0.861771;,
  -0.898319;-0.221144;0.379629;,
  -0.332136;-0.349345;0.876153;,
  0.450997;-0.226073;0.863419;,
  0.334088;0.342365;-0.878164;,
  -0.948293;0.018838;-0.316836;,
  0.000000;-1.000000;-0.000000;;
  11;
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,0,0,5;,
  4;0,1,1,0;,
  4;1,6,6,1;,
  4;6,2,2,6;,
  4;2,7,7,2;,
  4;7,3,3,7;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;;
 }
 MeshTextureCoords {
  24;
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.750000;,
  0.250000;0.750000;;
 }
}
