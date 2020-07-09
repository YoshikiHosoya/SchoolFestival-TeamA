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
 0.00000;22.11055;0.00000;,
 -15.79820;22.11055;0.00000;,
 -11.17100;22.11055;13.43495;,
 0.00000;22.11055;0.00000;,
 -11.17100;22.11055;-13.43495;,
 0.00000;22.11055;0.00000;,
 0.00000;22.11055;-18.99991;,
 0.00000;22.11055;0.00000;,
 11.17100;22.11055;-13.43495;,
 0.00000;22.11055;0.00000;,
 15.79820;22.11055;0.00000;,
 0.00000;22.11055;0.00000;,
 11.17100;22.11055;13.43495;,
 0.00000;22.11055;0.00000;,
 0.00000;22.11055;18.99991;,
 0.00000;22.11055;0.00000;,
 -11.17100;22.11055;13.43495;,
 0.00000;-22.07150;-0.00000;,
 -11.17100;-22.07150;13.43495;,
 -15.79820;-22.07150;0.00000;,
 0.00000;-22.07150;-0.00000;,
 -11.17100;-22.07150;-13.43495;,
 0.00000;-22.07150;-0.00000;,
 0.00000;-22.07150;-18.99991;,
 0.00000;-22.07150;-0.00000;,
 11.17100;-22.07150;-13.43495;,
 0.00000;-22.07150;-0.00000;,
 15.79820;-22.07150;-0.00000;,
 0.00000;-22.07150;-0.00000;,
 11.17100;-22.07150;13.43495;,
 0.00000;-22.07150;-0.00000;,
 0.00000;-22.07150;18.99991;,
 0.00000;-22.07150;-0.00000;,
 -11.17100;-22.07150;13.43495;,
 -14.47865;9.71480;17.41294;,
 -20.47590;9.71480;0.00000;,
 -20.47590;1.21060;0.00000;,
 -14.47865;1.21060;17.41294;,
 -14.47865;9.71480;-17.41294;,
 -14.47865;1.21060;-17.41294;,
 0.00000;9.71480;-24.62562;,
 0.00000;1.21060;-24.62562;,
 14.47865;9.71480;-17.41294;,
 14.47865;1.21060;-17.41294;,
 20.47590;9.71480;0.00000;,
 20.47590;1.21060;0.00000;,
 14.47865;9.71480;17.41294;,
 14.47865;1.21060;17.41294;,
 0.00000;9.71480;24.62562;,
 0.00000;1.21060;24.62562;,
 -14.47865;9.71480;17.41294;,
 -14.47865;1.21060;17.41294;,
 -11.64355;20.33960;14.00328;,
 -16.48605;20.28770;0.00000;,
 -11.64545;20.33265;-14.00556;,
 0.00000;20.44760;-19.75465;,
 11.58345;20.56480;-13.93099;,
 16.36215;20.61605;0.00000;,
 11.58160;20.57175;13.92876;,
 0.00000;20.45745;19.75014;,
 -11.64355;20.33960;14.00328;,
 -16.80545;-20.34530;0.00000;,
 -11.89670;-20.29265;14.30773;,
 -14.47865;-10.17295;17.41294;,
 -20.47590;-10.17295;0.00000;,
 -11.89490;-20.29975;-14.30556;,
 -14.47865;-10.17295;-17.41294;,
 0.00000;-20.18235;-20.28207;,
 0.00000;-10.17295;-24.62562;,
 11.95570;-20.06135;-14.37868;,
 14.47865;-10.17295;-17.41294;,
 16.92715;-20.00810;-0.00000;,
 20.47590;-10.17295;-0.00000;,
 11.95755;-20.05420;14.38091;,
 14.47865;-10.17295;17.41294;,
 0.00000;-20.17225;20.28640;,
 0.00000;-10.17295;24.62562;,
 -11.89670;-20.29265;14.30773;,
 -14.47865;-10.17295;17.41294;,
 -14.47865;-3.69560;17.41294;,
 -20.47590;-3.69560;0.00000;,
 -14.47865;-3.69560;-17.41294;,
 0.00000;-3.69560;-24.62562;,
 14.47865;-3.69560;-17.41294;,
 20.47590;-3.69560;-0.00000;,
 14.47865;-3.69560;17.41294;,
 0.00000;-3.69560;24.62562;,
 -14.47865;-3.69560;17.41294;;
 
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
    "C:\\Users\\game305\\Desktop\\SchoolFestival-TeamA\\���Ő���\\��METALSLUG\\data\\materialtexture\\images.jpg";
   }
  }
  Material {
   0.357600;0.357600;0.357600;1.000000;;
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
  61;
  0.000000;1.000000;0.000000;,
  -0.142396;-0.947423;0.286555;,
  0.000000;-1.000000;-0.000000;,
  -0.142308;-0.947494;-0.286364;,
  0.001159;-0.893202;-0.449654;,
  0.360951;-0.878922;-0.311787;,
  0.144230;-0.946453;0.288832;,
  0.001151;-0.893045;0.449966;,
  -0.751703;0.000000;0.659502;,
  -1.000000;0.000000;0.000000;,
  -0.751703;0.000000;-0.659502;,
  0.000000;0.000000;-1.000000;,
  0.751703;0.000000;-0.659502;,
  1.000000;0.000000;0.000000;,
  0.751703;0.000000;0.659502;,
  0.000000;0.000000;1.000000;,
  -0.739356;-0.187434;0.646700;,
  -0.984955;-0.172808;0.000000;,
  -0.739357;-0.187433;-0.646700;,
  0.000000;-0.204913;-0.978780;,
  0.739357;-0.187434;-0.646700;,
  0.984956;-0.172808;-0.000000;,
  0.739356;-0.187433;0.646700;,
  -0.000000;-0.204913;0.978780;,
  -0.738299;0.195164;0.645620;,
  -0.983659;0.180040;0.000000;,
  -0.738299;0.195163;-0.645620;,
  0.000001;0.213240;-0.977000;,
  0.738299;0.195164;-0.645620;,
  0.983659;0.180041;-0.000000;,
  0.738299;0.195165;0.645620;,
  0.000000;0.213241;0.977000;,
  -0.697075;0.380937;0.607432;,
  -0.935600;0.353062;0.000001;,
  -0.697073;0.380945;-0.607429;,
  0.000002;0.413276;-0.910606;,
  0.697075;0.380936;-0.607432;,
  0.935601;0.353058;-0.000000;,
  0.697075;0.380935;0.607433;,
  0.000000;0.413270;0.910609;,
  -0.673126;-0.451478;0.585721;,
  -0.906238;-0.422768;0.000023;,
  -0.673057;-0.451729;-0.585606;,
  0.001080;-0.482698;-0.875786;,
  0.676757;-0.443804;-0.587399;,
  0.911230;-0.411898;0.000018;,
  0.676811;-0.443586;0.587502;,
  0.001072;-0.482356;0.875975;,
  -0.697076;0.380934;0.607433;,
  -0.935600;0.353062;0.000002;,
  -0.697071;0.380953;-0.607427;,
  0.000003;0.413282;-0.910603;,
  0.697077;0.380933;-0.607432;,
  0.935603;0.353053;-0.000000;,
  0.697077;0.380931;0.607434;,
  0.000001;0.413267;0.910610;,
  -0.864797;-0.502122;0.000046;,
  -0.828805;-0.481053;0.285782;,
  -0.828679;-0.481321;-0.285695;,
  0.876483;-0.481432;0.000037;,
  0.839197;-0.460823;0.288775;;
  72;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;2,1,2;,
  3;2,2,3;,
  3;2,3,4;,
  3;2,4,5;,
  3;2,5,2;,
  3;2,2,6;,
  3;2,6,7;,
  3;2,7,1;,
  4;24,25,9,8;,
  4;25,26,10,9;,
  4;26,27,11,10;,
  4;27,28,12,11;,
  4;28,29,13,12;,
  4;29,30,14,13;,
  4;30,31,15,14;,
  4;31,24,8,15;,
  4;32,48,49,33;,
  4;32,33,25,24;,
  4;33,49,50,34;,
  4;33,34,26,25;,
  4;34,50,51,35;,
  4;34,35,27,26;,
  4;35,51,52,36;,
  4;35,36,28,27;,
  4;36,52,53,37;,
  4;36,37,29,28;,
  4;37,53,54,38;,
  4;37,38,30,29;,
  4;38,54,55,39;,
  4;38,39,31,30;,
  4;39,55,48,32;,
  4;39,32,24,31;,
  4;41,56,57,40;,
  4;41,40,16,17;,
  4;42,58,56,41;,
  4;42,41,17,18;,
  4;43,4,3,42;,
  4;43,42,18,19;,
  4;44,5,4,43;,
  4;44,43,19,20;,
  4;45,59,5,44;,
  4;45,44,20,21;,
  4;46,60,59,45;,
  4;46,45,21,22;,
  4;47,7,6,46;,
  4;47,46,22,23;,
  4;40,1,7,47;,
  4;40,47,23,16;,
  4;8,8,9,9;,
  4;8,9,17,16;,
  4;9,9,10,10;,
  4;9,10,18,17;,
  4;10,10,11,11;,
  4;10,11,19,18;,
  4;11,11,12,12;,
  4;11,12,20,19;,
  4;12,12,13,13;,
  4;12,13,21,20;,
  4;13,13,14,14;,
  4;13,14,22,21;,
  4;14,14,15,15;,
  4;14,15,23,22;,
  4;15,15,8,8;,
  4;15,8,16,23;;
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
  0.000000;0.250240;,
  0.125000;0.250240;,
  0.125000;0.513880;,
  0.000000;0.513880;,
  0.250000;0.250240;,
  0.250000;0.513880;,
  0.375000;0.250240;,
  0.375000;0.513880;,
  0.500000;0.250240;,
  0.500000;0.513880;,
  0.625000;0.250240;,
  0.625000;0.513880;,
  0.750000;0.250240;,
  0.750000;0.513880;,
  0.875000;0.250240;,
  0.875000;0.513880;,
  1.000000;0.250240;,
  1.000000;0.513880;,
  0.000000;0.035750;,
  0.125000;0.036800;,
  0.250000;0.035890;,
  0.375000;0.033570;,
  0.500000;0.031200;,
  0.625000;0.030170;,
  0.750000;0.031060;,
  0.875000;0.033370;,
  1.000000;0.035750;,
  0.125000;0.943130;,
  0.000000;0.942050;,
  0.000000;0.735880;,
  0.125000;0.735880;,
  0.250000;0.942200;,
  0.250000;0.735880;,
  0.375000;0.939810;,
  0.375000;0.735880;,
  0.500000;0.937340;,
  0.500000;0.735880;,
  0.625000;0.936260;,
  0.625000;0.735880;,
  0.750000;0.937190;,
  0.750000;0.735880;,
  0.875000;0.939600;,
  0.875000;0.735880;,
  1.000000;0.942050;,
  1.000000;0.735880;,
  0.000000;0.591120;,
  0.125000;0.591120;,
  0.250000;0.591120;,
  0.375000;0.591120;,
  0.500000;0.591120;,
  0.625000;0.591120;,
  0.750000;0.591120;,
  0.875000;0.591120;,
  1.000000;0.591120;;
 }
}
