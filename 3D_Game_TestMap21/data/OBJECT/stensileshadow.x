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
 0.00000;56.32437;-10.79576;,
 5.87168;56.32437;-9.07168;,
 5.87168;-30.33585;-9.07168;,
 0.00000;-30.33585;-10.79576;,
 9.87913;56.32437;-4.44683;,
 9.87913;-30.33585;-4.44683;,
 10.75003;56.32437;1.61044;,
 10.75003;-30.33585;1.61044;,
 8.20788;56.32437;7.17699;,
 8.20788;-30.33585;7.17699;,
 3.05978;56.32437;10.48548;,
 3.05978;-30.33585;10.48548;,
 -3.05978;56.32437;10.48546;,
 -3.05978;-30.33585;10.48546;,
 -8.20788;56.32437;7.17699;,
 -8.20788;-30.33585;7.17699;,
 -10.75003;56.32437;1.61044;,
 -10.75003;-30.33585;1.61044;,
 -9.87913;56.32437;-4.44683;,
 -9.87913;-30.33585;-4.44683;,
 -5.87168;56.32437;-9.07168;,
 -5.87168;-30.33585;-9.07168;,
 0.00000;56.32437;-10.79576;,
 0.00000;-30.33585;-10.79576;,
 0.00000;56.32437;0.06482;,
 0.00000;56.32437;0.06482;,
 0.00000;56.32437;0.06482;,
 0.00000;56.32437;0.06482;,
 0.00000;56.32437;0.06482;,
 0.00000;56.32437;0.06482;,
 0.00000;56.32437;0.06482;,
 0.00000;56.32437;0.06482;,
 0.00000;56.32437;0.06482;,
 0.00000;56.32437;0.06482;,
 0.00000;56.32437;0.06482;,
 0.00000;-30.33585;0.06482;,
 0.00000;-30.33585;0.06482;,
 0.00000;-30.33585;0.06482;,
 0.00000;-30.33585;0.06482;,
 0.00000;-30.33585;0.06482;,
 0.00000;-30.33585;0.06482;,
 0.00000;-30.33585;0.06482;,
 0.00000;-30.33585;0.06482;,
 0.00000;-30.33585;0.06482;,
 0.00000;-30.33585;0.06482;,
 0.00000;-30.33585;0.06482;;
 
 33;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 3;24,1,0;,
 3;25,4,1;,
 3;26,6,4;,
 3;27,8,6;,
 3;28,10,8;,
 3;29,12,10;,
 3;30,14,12;,
 3;31,16,14;,
 3;32,18,16;,
 3;33,20,18;,
 3;34,22,20;,
 3;35,3,2;,
 3;36,2,5;,
 3;37,5,7;,
 3;38,7,9;,
 3;39,9,11;,
 3;40,11,13;,
 3;41,13,15;,
 3;42,15,17;,
 3;43,17,19;,
 3;44,19,21;,
 3;45,21,23;;
 
 MeshMaterialList {
  4;
  33;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
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
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  13;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.540641;0.000000;-0.841254;,
  0.909632;0.000000;-0.415415;,
  0.989821;0.000000;0.142315;,
  0.755750;0.000000;0.654860;,
  0.281732;0.000000;0.959493;,
  -0.281733;0.000000;0.959493;,
  -0.755749;0.000000;0.654861;,
  -0.989821;0.000000;0.142315;,
  -0.909632;0.000000;-0.415415;,
  -0.540641;0.000000;-0.841254;,
  0.000000;-1.000000;-0.000000;;
  33;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,1,1,11;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;,
  3;12,12,12;;
 }
 MeshTextureCoords {
  46;
  0.000000;0.000000;,
  0.090910;0.000000;,
  0.090910;1.000000;,
  0.000000;1.000000;,
  0.181820;0.000000;,
  0.181820;1.000000;,
  0.272730;0.000000;,
  0.272730;1.000000;,
  0.363640;0.000000;,
  0.363640;1.000000;,
  0.454550;0.000000;,
  0.454550;1.000000;,
  0.545450;0.000000;,
  0.545450;1.000000;,
  0.636360;0.000000;,
  0.636360;1.000000;,
  0.727270;0.000000;,
  0.727270;1.000000;,
  0.818180;0.000000;,
  0.818180;1.000000;,
  0.909090;0.000000;,
  0.909090;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.045450;0.000000;,
  0.136360;0.000000;,
  0.227270;0.000000;,
  0.318180;0.000000;,
  0.409090;0.000000;,
  0.500000;0.000000;,
  0.590910;0.000000;,
  0.681820;0.000000;,
  0.772730;0.000000;,
  0.863640;0.000000;,
  0.954550;0.000000;,
  0.045450;1.000000;,
  0.136360;1.000000;,
  0.227270;1.000000;,
  0.318180;1.000000;,
  0.409090;1.000000;,
  0.500000;1.000000;,
  0.590910;1.000000;,
  0.681820;1.000000;,
  0.772730;1.000000;,
  0.863640;1.000000;,
  0.954550;1.000000;;
 }
}
