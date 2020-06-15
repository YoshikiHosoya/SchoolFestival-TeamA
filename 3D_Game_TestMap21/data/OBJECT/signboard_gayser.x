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
 30;
 -2.20204;86.17405;0.59004;,
 -2.20204;0.02210;0.59004;,
 0.59004;0.02210;2.20204;,
 0.59004;86.17405;2.20204;,
 -0.59004;86.17405;-2.20204;,
 -0.59004;0.02210;-2.20204;,
 2.20204;86.17405;-0.59004;,
 2.20204;0.02210;-0.59004;,
 0.59004;86.17405;2.20204;,
 0.59004;0.02210;2.20204;,
 30.84190;82.12390;20.29842;,
 -32.99994;82.12390;-16.56064;,
 -32.99994;42.00807;-16.56064;,
 30.84190;42.00807;20.29842;,
 -32.99994;82.12390;-16.56064;,
 -30.84190;82.12390;-20.29842;,
 -30.84190;42.00807;-20.29842;,
 -32.99994;42.00807;-16.56064;,
 -30.84190;82.12390;-20.29842;,
 32.99994;82.12390;16.56064;,
 32.99994;42.00807;16.56064;,
 -30.84190;42.00807;-20.29842;,
 32.99994;82.12390;16.56064;,
 30.84190;82.12390;20.29842;,
 30.84190;42.00807;20.29842;,
 32.99994;42.00807;16.56064;,
 -32.99994;82.12390;-16.56064;,
 30.84190;82.12390;20.29842;,
 30.84190;42.00807;20.29842;,
 -32.99994;42.00807;-16.56064;;
 
 16;
 3;0,1,2;,
 3;0,2,3;,
 3;4,5,1;,
 3;4,1,0;,
 3;6,7,5;,
 3;6,5,4;,
 3;8,9,7;,
 3;8,7,6;,
 4;10,11,12,13;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;22,15,26,27;,
 4;28,29,16,25;,
 3;6,4,0;,
 3;3,6,0;;
 
 MeshMaterialList {
  2;
  16;
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
  1,
  0,
  0,
  0,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game307\\Pictures\\�Q�[���e�N�X�`��\\3D�����V�[�g\\ita.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game307\\Desktop\\effect\\pictogram\\gayser_caution.png";
   }
  }
 }
 MeshNormals {
  14;
  -0.499998;0.000000;0.866027;,
  -0.499998;0.000000;0.866027;,
  -0.866027;0.000000;-0.499998;,
  0.499998;0.000000;-0.866027;,
  -0.866027;0.000000;-0.499998;,
  0.499998;0.000000;-0.866027;,
  -0.500000;0.000000;0.866026;,
  -0.866022;0.000000;-0.500006;,
  0.500000;0.000000;-0.866026;,
  0.866027;0.000000;0.499998;,
  0.866027;0.000000;0.499998;,
  0.866022;0.000000;0.500006;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  16;
  3;1,0,1;,
  3;1,1,0;,
  3;2,4,2;,
  3;2,2,4;,
  3;3,5,3;,
  3;3,3,5;,
  3;9,10,9;,
  3;9,9,10;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  3;12,12,12;,
  3;12,12,12;;
 }
 MeshTextureCoords {
  30;
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
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