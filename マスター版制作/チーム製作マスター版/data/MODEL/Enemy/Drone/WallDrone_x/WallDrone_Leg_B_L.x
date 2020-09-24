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
 -4.91727;-26.84200;5.35240;,
 -6.48517;-4.23080;-3.61440;,
 -1.86587;-2.15970;-9.35470;,
 0.49473;-26.84200;-0.05950;,
 3.87443;2.84030;-10.14720;,
 8.14843;-26.84200;-0.05950;,
 7.37303;7.84030;-5.52790;,
 13.56033;-26.84200;5.35240;,
 6.58033;9.91130;1.79750;,
 13.56033;-26.84200;13.00609;,
 1.96103;7.84030;7.53781;,
 8.14833;-26.84200;18.41809;,
 -3.77927;2.84030;8.33040;,
 0.49473;-26.84200;18.41809;,
 -7.27777;-2.15970;3.71100;,
 -4.91727;-26.84200;13.00609;,
 -6.48517;-4.23080;-3.61440;,
 -4.91727;-26.84200;5.35240;,
 0.49473;-26.84200;-0.05950;,
 8.14843;-26.84200;-0.05950;,
 8.14833;-26.84200;18.41809;,
 8.14843;-26.84200;-0.05950;,
 -4.91727;-26.84200;13.00609;,
 -4.91727;-26.84200;5.35240;;
 
 11;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;11,13,18,19;,
 4;7,9,20,21;,
 4;18,13,22,23;;
 
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
  0.941350;0.055046;-0.332912;,
  0.886340;0.277882;0.370382;,
  -0.448741;0.236606;0.861771;,
  -0.898319;-0.221144;-0.379629;,
  -0.332136;-0.349345;-0.876153;,
  0.450997;-0.226073;-0.863419;,
  0.334088;0.342365;0.878164;,
  -0.948293;0.018838;0.316836;,
  0.000000;-1.000000;-0.000000;;
  11;
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,0,0;,
  4;0,0,1,1;,
  4;1,1,6,6;,
  4;6,6,2,2;,
  4;2,2,7,7;,
  4;7,7,3,3;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;;
 }
 MeshTextureCoords {
  24;
  0.250000;0.000000;,
  0.375000;0.000000;,
  0.375000;0.125000;,
  0.250000;0.125000;,
  0.375000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.875000;,
  0.250000;0.875000;,
  0.375000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.750000;,
  0.250000;0.625000;,
  0.250000;0.500000;,
  0.250000;0.375000;,
  0.250000;0.750000;,
  0.250000;0.750000;;
 }
}
