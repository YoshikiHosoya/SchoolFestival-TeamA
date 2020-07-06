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
 88;
 0.00000;45.09160;-0.00000;,
 -15.79819;45.09160;-0.00000;,
 -11.17101;45.09160;11.17101;,
 0.00000;45.09160;-0.00000;,
 -11.17101;45.09160;-11.17102;,
 0.00000;45.09160;-0.00000;,
 0.00000;45.09160;-15.79819;,
 0.00000;45.09160;-0.00000;,
 11.17102;45.09160;-11.17102;,
 0.00000;45.09160;-0.00000;,
 15.79819;45.09160;0.00000;,
 0.00000;45.09160;-0.00000;,
 11.17102;45.09160;11.17101;,
 0.00000;45.09160;-0.00000;,
 0.00000;45.09160;15.79818;,
 0.00000;45.09160;-0.00000;,
 -11.17101;45.09160;11.17101;,
 0.00000;0.90956;-0.00000;,
 -11.17101;0.90956;11.17101;,
 -15.79819;0.90956;-0.00000;,
 0.00000;0.90956;-0.00000;,
 -11.17101;0.90956;-11.17102;,
 0.00000;0.90956;-0.00000;,
 0.00000;0.90956;-15.79819;,
 0.00000;0.90956;-0.00000;,
 11.17102;0.90956;-11.17102;,
 0.00000;0.90956;-0.00000;,
 15.79819;0.90956;0.00000;,
 0.00000;0.90956;-0.00000;,
 11.17102;0.90956;11.17101;,
 0.00000;0.90956;-0.00000;,
 0.00000;0.90956;15.79818;,
 0.00000;0.90956;-0.00000;,
 -11.17101;0.90956;11.17101;,
 -14.47866;32.69583;14.47866;,
 -20.47591;32.69583;-0.00000;,
 -20.47591;24.19166;-0.00000;,
 -14.47866;24.19166;14.47866;,
 -14.47866;32.69583;-14.47866;,
 -14.47866;24.19166;-14.47866;,
 0.00000;32.69583;-20.47591;,
 0.00000;24.19166;-20.47591;,
 14.47866;32.69583;-14.47866;,
 14.47866;24.19166;-14.47866;,
 20.47591;32.69583;0.00000;,
 20.47591;24.19166;0.00000;,
 14.47866;32.69583;14.47866;,
 14.47866;24.19166;14.47866;,
 0.00000;32.69583;20.47590;,
 0.00000;24.19166;20.47590;,
 -14.47866;32.69583;14.47866;,
 -14.47866;24.19166;14.47866;,
 -11.64356;43.32067;11.64356;,
 -16.48606;43.26876;-0.00000;,
 -11.64544;43.31369;-11.64544;,
 0.00000;43.42865;-16.42575;,
 11.58347;43.54585;-11.58347;,
 16.36215;43.59710;0.00000;,
 11.58162;43.55281;11.58162;,
 0.00000;43.43852;16.42202;,
 -11.64356;43.32067;11.64356;,
 -16.80547;2.63577;-0.00000;,
 -11.89670;2.68842;11.89670;,
 -14.47866;12.80812;14.47866;,
 -20.47591;12.80812;-0.00000;,
 -11.89489;2.68128;-11.89489;,
 -14.47866;12.80812;-14.47866;,
 0.00000;2.79871;-16.86428;,
 0.00000;12.80812;-20.47591;,
 11.95571;2.91968;-11.95571;,
 14.47866;12.80812;-14.47866;,
 16.92715;2.97294;0.00000;,
 20.47591;12.80812;0.00000;,
 11.95754;2.92686;11.95754;,
 14.47866;12.80812;14.47866;,
 0.00000;2.80882;16.86792;,
 0.00000;12.80812;20.47590;,
 -11.89670;2.68842;11.89670;,
 -14.47866;12.80812;14.47866;,
 -14.47866;19.28547;14.47866;,
 -20.47591;19.28547;-0.00000;,
 -14.47866;19.28547;-14.47866;,
 0.00000;19.28547;-20.47591;,
 14.47866;19.28547;-14.47866;,
 20.47591;19.28547;0.00000;,
 14.47866;19.28547;14.47866;,
 0.00000;19.28547;20.47590;,
 -14.47866;19.28547;14.47866;;
 
 72;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,19;,
 3;20,19,21;,
 3;22,21,23;,
 3;24,23,25;,
 3;26,25,27;,
 3;28,27,29;,
 3;30,29,31;,
 3;32,31,33;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;52,2,1,53;,
 4;52,53,35,34;,
 4;53,1,4,54;,
 4;53,54,38,35;,
 4;54,4,6,55;,
 4;54,55,40,38;,
 4;55,6,8,56;,
 4;55,56,42,40;,
 4;56,8,10,57;,
 4;56,57,44,42;,
 4;57,10,12,58;,
 4;57,58,46,44;,
 4;58,12,14,59;,
 4;58,59,48,46;,
 4;59,14,16,60;,
 4;59,60,50,48;,
 4;61,19,18,62;,
 4;61,62,63,64;,
 4;65,21,19,61;,
 4;65,61,64,66;,
 4;67,23,21,65;,
 4;67,65,66,68;,
 4;69,25,23,67;,
 4;69,67,68,70;,
 4;71,27,25,69;,
 4;71,69,70,72;,
 4;73,29,27,71;,
 4;73,71,72,74;,
 4;75,31,29,73;,
 4;75,73,74,76;,
 4;77,33,31,75;,
 4;77,75,76,78;,
 4;79,37,36,80;,
 4;79,80,64,63;,
 4;80,36,39,81;,
 4;80,81,66,64;,
 4;81,39,41,82;,
 4;81,82,68,66;,
 4;82,41,43,83;,
 4;82,83,70,68;,
 4;83,43,45,84;,
 4;83,84,72,70;,
 4;84,45,47,85;,
 4;84,85,74,72;,
 4;85,47,49,86;,
 4;85,86,76,74;,
 4;86,49,51,87;,
 4;86,87,78,76;;
 
 MeshMaterialList {
  3;
  72;
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
  0,
  0,
  0,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "D:\\ピクチャ２\\マテリアルテクスチャ\\images.jpg";
   }
  }
  Material {
   0.357647;0.357647;0.357647;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  64;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;-0.000000;,
  -0.707107;0.000000;-0.707107;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;-0.000000;0.707107;,
  0.000000;-0.000000;1.000000;,
  -0.696443;-0.173012;0.696443;,
  -0.984920;-0.173012;-0.000000;,
  -0.696444;-0.173011;-0.696443;,
  0.000000;-0.173011;-0.984920;,
  0.696444;-0.173011;-0.696443;,
  0.984920;-0.173011;0.000000;,
  0.696443;-0.173011;0.696444;,
  0.000000;-0.173011;0.984920;,
  -0.695522;0.180270;0.695522;,
  -0.983617;0.180270;0.000000;,
  -0.695523;0.180269;-0.695522;,
  0.000000;0.180269;-0.983617;,
  0.695523;0.180270;-0.695522;,
  0.983617;0.180270;0.000000;,
  0.695522;0.180270;0.695522;,
  -0.000000;0.180270;0.983617;,
  -0.661569;0.353063;0.661569;,
  -0.935600;0.353063;0.000001;,
  -0.661569;0.353065;-0.661568;,
  0.000001;0.353065;-0.935599;,
  0.661570;0.353062;-0.661569;,
  0.935600;0.353061;-0.000000;,
  0.661569;0.353063;0.661568;,
  -0.000000;0.353064;0.935599;,
  -0.640939;-0.420967;0.641860;,
  -0.906212;-0.422823;0.000028;,
  -0.640882;-0.421216;-0.641753;,
  0.000835;-0.417281;-0.908777;,
  0.644208;-0.413539;-0.643413;,
  0.911189;-0.411988;0.000022;,
  0.644232;-0.413396;0.643482;,
  0.000806;-0.417022;0.908896;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;-0.000000;,
  -0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.707107;-0.000000;0.707107;,
  0.000000;-0.000000;1.000000;,
  -0.661569;0.353064;0.661568;,
  -0.935599;0.353064;0.000001;,
  -0.661568;0.353069;-0.661567;,
  0.000001;0.353068;-0.935598;,
  0.661570;0.353062;-0.661568;,
  0.935601;0.353060;-0.000000;,
  0.661569;0.353064;0.661568;,
  -0.000000;0.353067;0.935598;,
  -0.864864;-0.502006;0.000056;,
  -0.612072;-0.498495;0.613898;,
  -0.611930;-0.498966;-0.613657;,
  0.001655;-0.491508;-0.870872;,
  0.619401;-0.484392;-0.617824;,
  0.876482;-0.481435;0.000044;,
  0.619464;-0.484119;0.617976;,
  0.001600;-0.491014;0.871150;;
  72;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;18,19,3,2;,
  4;19,20,4,3;,
  4;20,21,5,4;,
  4;21,22,6,5;,
  4;22,23,7,6;,
  4;23,24,8,7;,
  4;24,25,9,8;,
  4;25,18,2,9;,
  4;26,48,49,27;,
  4;26,27,19,18;,
  4;27,49,50,28;,
  4;27,28,20,19;,
  4;28,50,51,29;,
  4;28,29,21,20;,
  4;29,51,52,30;,
  4;29,30,22,21;,
  4;30,52,53,31;,
  4;30,31,23,22;,
  4;31,53,54,32;,
  4;31,32,24,23;,
  4;32,54,55,33;,
  4;32,33,25,24;,
  4;33,55,48,26;,
  4;33,26,18,25;,
  4;35,56,57,34;,
  4;35,34,10,11;,
  4;36,58,56,35;,
  4;36,35,11,12;,
  4;37,59,58,36;,
  4;37,36,12,13;,
  4;38,60,59,37;,
  4;38,37,13,14;,
  4;39,61,60,38;,
  4;39,38,14,15;,
  4;40,62,61,39;,
  4;40,39,15,16;,
  4;41,63,62,40;,
  4;41,40,16,17;,
  4;34,57,63,41;,
  4;34,41,17,10;,
  4;42,2,3,43;,
  4;42,43,11,10;,
  4;43,3,4,4;,
  4;43,4,12,11;,
  4;4,4,5,44;,
  4;4,44,13,12;,
  4;44,5,6,6;,
  4;44,6,14,13;,
  4;6,6,7,45;,
  4;6,45,15,14;,
  4;45,7,8,46;,
  4;45,46,16,15;,
  4;46,8,9,47;,
  4;46,47,17,16;,
  4;47,9,2,42;,
  4;47,42,10,17;;
 }
 MeshTextureCoords {
  88;
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.000000;0.250244;,
  0.125000;0.250244;,
  0.125000;0.513875;,
  0.000000;0.513875;,
  0.250000;0.250244;,
  0.250000;0.513875;,
  0.375000;0.250244;,
  0.375000;0.513875;,
  0.500000;0.250244;,
  0.500000;0.513875;,
  0.625000;0.250244;,
  0.625000;0.513875;,
  0.750000;0.250244;,
  0.750000;0.513875;,
  0.875000;0.250244;,
  0.875000;0.513875;,
  1.000000;0.250244;,
  1.000000;0.513875;,
  0.000000;0.035751;,
  0.125000;0.036799;,
  0.250000;0.035893;,
  0.375000;0.033571;,
  0.500000;0.031205;,
  0.625000;0.030170;,
  0.750000;0.031065;,
  0.875000;0.033373;,
  1.000000;0.035751;,
  0.125000;0.943125;,
  0.000000;0.942053;,
  0.000000;0.735881;,
  0.125000;0.735881;,
  0.250000;0.942198;,
  0.250000;0.735881;,
  0.375000;0.939806;,
  0.375000;0.735881;,
  0.500000;0.937341;,
  0.500000;0.735881;,
  0.625000;0.936256;,
  0.625000;0.735881;,
  0.750000;0.937195;,
  0.750000;0.735881;,
  0.875000;0.939600;,
  0.875000;0.735881;,
  1.000000;0.942053;,
  1.000000;0.735881;,
  0.000000;0.591118;,
  0.125000;0.591118;,
  0.250000;0.591118;,
  0.375000;0.591118;,
  0.500000;0.591118;,
  0.625000;0.591118;,
  0.750000;0.591118;,
  0.875000;0.591118;,
  1.000000;0.591118;;
 }
}
