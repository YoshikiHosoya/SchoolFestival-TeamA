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
 -15.57080;-14.50291;-20.41499;,
 8.03078;-2.57671;4.64261;,
 2.91379;-1.24701;10.17681;,
 -20.19011;-12.43181;-14.67469;,
 -4.02782;1.96319;10.47171;,
 -25.93040;-7.43181;-13.88219;,
 -8.72782;5.17339;5.35471;,
 -29.42900;-2.43181;-18.50149;,
 -8.43292;6.50309;-2.17679;,
 -28.63630;-0.36081;-25.82689;,
 -3.31581;5.17339;-7.71099;,
 -24.01700;-2.43181;-31.56719;,
 3.62578;1.96319;-8.00589;,
 -18.27670;-7.43181;-32.35979;,
 8.32568;-1.24701;-2.88879;,
 -14.77820;-12.43181;-27.74039;,
 8.03078;-2.57671;4.64261;,
 -15.57080;-14.50291;-20.41499;,
 2.91379;-1.24701;10.17681;,
 8.03078;-2.57671;4.64261;,
 -3.31581;5.17339;-7.71099;,
 8.03078;-2.57671;4.64261;,
 -8.72782;5.17339;5.35471;,
 -4.02782;1.96319;10.47171;;
 
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
  0.343089;-0.932731;0.110921;,
  -0.156064;-0.842174;0.516126;,
  -0.617404;-0.354927;0.702025;,
  -0.752689;0.023075;0.657971;,
  -0.260467;0.963004;-0.069142;,
  0.206601;0.862053;-0.462797;,
  0.626232;0.359253;-0.691933;,
  0.741779;-0.487008;-0.461073;,
  0.096161;0.993556;0.059999;,
  0.334688;0.930895;-0.146348;,
  -0.489090;0.857484;0.159724;,
  -0.039103;0.981545;0.187190;,
  0.419433;0.891007;0.173733;,
  0.419433;0.891007;0.173734;,
  0.419434;0.891006;0.173734;,
  0.419433;0.891007;0.173730;;
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
