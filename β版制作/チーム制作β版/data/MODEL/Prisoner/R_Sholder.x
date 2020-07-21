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
 142;
 -0.96895;0.94360;2.49380;,
 -0.84850;-0.03450;2.25235;,
 0.04980;0.94360;2.49380;,
 0.04055;-0.03450;2.25235;,
 -2.19885;1.82815;-1.28220;,
 -2.69950;-0.16115;-1.28220;,
 -2.19885;1.82815;0.07815;,
 -2.69950;-0.16115;0.07815;,
 0.04055;-0.03450;-2.35445;,
 -0.84850;-0.03450;-2.35445;,
 0.04980;0.94360;-2.59590;,
 -0.96895;0.94360;-2.59590;,
 2.15325;1.82815;0.07815;,
 2.65390;-0.16115;0.07815;,
 2.15325;1.82815;-1.28220;,
 2.65390;-0.16115;-1.28220;,
 -0.96895;1.82815;-1.28220;,
 -0.96895;1.82815;0.07815;,
 0.04980;1.82815;-1.28220;,
 0.04980;1.82815;0.07815;,
 -0.61040;-8.18435;-1.11255;,
 0.02045;-8.20355;-1.08405;,
 -0.58655;-8.20355;0.25650;,
 0.02045;-8.20355;0.25650;,
 2.31315;-2.30070;0.15760;,
 2.31315;-2.30070;-1.20800;,
 0.04055;-2.30070;-2.35445;,
 -0.84850;-2.30070;-2.35445;,
 -2.35875;-2.30070;-1.20800;,
 -2.35875;-2.30070;0.15760;,
 -0.84850;-2.30070;2.25235;,
 0.04055;-2.30070;2.25235;,
 2.06205;-4.63305;0.15760;,
 2.06205;-4.63305;-1.20800;,
 0.03375;-4.63305;-2.35445;,
 -0.75975;-4.63305;-2.35445;,
 -2.10765;-4.63305;-1.20800;,
 -2.10765;-4.63305;0.15760;,
 -0.75975;-4.63305;2.25235;,
 0.03375;-4.63305;2.25235;,
 1.57215;-7.12965;0.25650;,
 1.57215;-7.12965;-1.08405;,
 0.03375;-6.96470;-2.35445;,
 -0.75975;-6.96470;-2.35445;,
 -1.61775;-7.12965;-1.08405;,
 -1.61775;-7.12965;0.25650;,
 -0.75975;-6.96470;2.25235;,
 0.03375;-6.96470;2.25235;,
 1.27380;-8.20355;-1.08405;,
 1.27380;-8.20355;0.25650;,
 -0.61040;-7.63215;-1.93265;,
 0.02045;-7.61300;-1.96110;,
 -1.31940;-8.20355;0.25650;,
 -1.29560;-8.18435;-1.11255;,
 0.02045;-7.61300;1.85900;,
 -0.58655;-7.61300;1.85900;,
 -1.31940;-8.20355;1.23795;,
 -1.61775;-7.12965;1.23795;,
 -2.10765;-4.63305;1.44050;,
 -2.35875;-2.30070;1.44050;,
 -2.69950;-0.16115;1.56355;,
 -2.19885;1.82815;1.56355;,
 -0.96895;1.82815;1.56355;,
 0.04980;1.82815;1.56355;,
 2.15325;1.82815;1.56355;,
 2.65390;-0.16115;1.56355;,
 2.31315;-2.30070;1.44050;,
 2.06205;-4.63305;1.44050;,
 1.57215;-7.12965;1.23795;,
 1.27380;-8.20355;1.23795;,
 -0.58655;-8.20355;1.23795;,
 0.02045;-8.20355;1.23795;,
 1.27380;-7.61300;-1.96110;,
 1.27380;-7.12965;-1.96110;,
 1.67210;-4.63305;-2.35445;,
 1.87620;-2.30070;-2.35445;,
 2.15325;-0.16115;-2.59590;,
 2.15325;0.94360;-2.59590;,
 -0.96895;0.94360;-2.59590;,
 0.04980;0.94360;-2.59590;,
 -2.19885;-0.16115;-2.59590;,
 -2.19885;0.94360;-2.59590;,
 -1.92180;-2.30070;-2.35445;,
 -1.71770;-4.63305;-2.35445;,
 -1.31940;-7.12965;-1.96110;,
 -1.29560;-7.63215;-1.93265;,
 0.02045;-7.61300;-1.96110;,
 -0.61040;-7.63215;-1.93265;,
 -1.31940;-7.61300;1.85900;,
 -1.31940;-7.12965;1.85900;,
 -1.71770;-4.63305;2.25235;,
 -1.92180;-2.30070;2.25235;,
 -2.19885;-0.16115;2.49380;,
 -2.19885;0.94360;2.49380;,
 2.15325;-0.16115;2.49380;,
 2.15325;0.94360;2.49380;,
 1.87620;-2.30070;2.25235;,
 1.67210;-4.63305;2.25235;,
 1.27380;-7.12965;1.85900;,
 1.27380;-7.61300;1.85900;,
 0.75065;-6.96470;2.25235;,
 0.56890;-7.61300;1.85900;,
 0.75065;-4.63305;2.25235;,
 0.84380;-2.30070;2.25235;,
 0.84380;-0.03450;2.25235;,
 0.97020;0.94360;2.49380;,
 0.97020;1.82815;1.56355;,
 0.97020;1.82815;0.07815;,
 0.97020;1.82815;-1.28220;,
 0.97020;0.94360;-2.59590;,
 0.97020;0.94360;-2.59590;,
 0.84380;-0.03450;-2.35445;,
 0.84380;-2.30070;-2.35445;,
 0.75065;-4.63305;-2.35445;,
 0.75065;-6.96470;-2.35445;,
 0.56890;-7.61300;-1.96110;,
 0.56890;-7.61300;-1.96110;,
 0.56890;-8.20355;-1.08405;,
 0.56890;-8.20355;0.25650;,
 0.56890;-8.20355;1.23795;,
 -2.19885;1.82815;-1.28220;,
 -2.19885;0.94360;-2.59590;,
 -2.19885;1.82815;0.07815;,
 -2.19885;1.82815;1.56355;,
 -1.31940;-8.20355;1.23795;,
 -1.31940;-8.20355;0.25650;,
 -1.29560;-8.18435;-1.11255;,
 -1.29560;-7.63215;-1.93265;,
 1.27380;-7.12965;1.85900;,
 1.27380;-7.61300;1.85900;,
 1.67210;-4.63305;2.25235;,
 1.87620;-2.30070;2.25235;,
 2.15325;-0.16115;2.49380;,
 2.15325;0.94360;2.49380;,
 2.15325;1.82815;1.56355;,
 2.15325;1.82815;0.07815;,
 2.15325;1.82815;-1.28220;,
 2.15325;0.94360;-2.59590;,
 1.27380;-7.61300;-1.96110;,
 1.27380;-8.20355;-1.08405;,
 1.27380;-8.20355;0.25650;,
 1.27380;-8.20355;1.23795;;
 
 224;
 3;0,1,2;,
 3;2,1,3;,
 3;4,5,6;,
 3;6,5,7;,
 3;8,9,10;,
 3;10,9,11;,
 3;12,13,14;,
 3;14,13,15;,
 3;16,17,18;,
 3;18,17,19;,
 3;20,21,22;,
 3;22,21,23;,
 3;24,25,13;,
 3;13,25,15;,
 3;8,26,9;,
 3;9,26,27;,
 3;5,28,7;,
 3;7,28,29;,
 3;1,30,3;,
 3;3,30,31;,
 3;24,32,25;,
 3;25,32,33;,
 3;34,35,26;,
 3;26,35,27;,
 3;28,36,29;,
 3;29,36,37;,
 3;30,38,31;,
 3;31,38,39;,
 3;40,41,32;,
 3;32,41,33;,
 3;34,42,35;,
 3;35,42,43;,
 3;36,44,37;,
 3;37,44,45;,
 3;38,46,39;,
 3;39,46,47;,
 3;48,41,49;,
 3;49,41,40;,
 3;43,42,50;,
 3;50,42,51;,
 3;45,44,52;,
 3;52,44,53;,
 3;54,47,55;,
 3;55,47,46;,
 3;56,57,52;,
 3;52,57,45;,
 3;45,57,37;,
 3;37,57,58;,
 3;29,37,59;,
 3;59,37,58;,
 3;29,59,7;,
 3;7,59,60;,
 3;6,7,61;,
 3;61,7,60;,
 3;17,62,19;,
 3;19,62,63;,
 3;64,65,12;,
 3;12,65,13;,
 3;65,66,13;,
 3;13,66,24;,
 3;66,67,24;,
 3;24,67,32;,
 3;67,68,32;,
 3;32,68,40;,
 3;49,40,69;,
 3;69,40,68;,
 3;70,22,71;,
 3;71,22,23;,
 3;72,73,48;,
 3;48,73,41;,
 3;41,73,33;,
 3;33,73,74;,
 3;25,33,75;,
 3;75,33,74;,
 3;25,75,15;,
 3;15,75,76;,
 3;15,76,14;,
 3;14,76,77;,
 3;78,16,79;,
 3;79,16,18;,
 3;5,4,80;,
 3;80,4,81;,
 3;28,5,82;,
 3;82,5,80;,
 3;83,36,82;,
 3;82,36,28;,
 3;44,36,84;,
 3;84,36,83;,
 3;44,84,53;,
 3;53,84,85;,
 3;86,21,87;,
 3;87,21,20;,
 3;88,89,56;,
 3;56,89,57;,
 3;57,89,58;,
 3;58,89,90;,
 3;59,58,91;,
 3;91,58,90;,
 3;59,91,60;,
 3;60,91,92;,
 3;60,92,61;,
 3;61,92,93;,
 3;2,63,0;,
 3;0,63,62;,
 3;65,64,94;,
 3;94,64,95;,
 3;66,65,96;,
 3;96,65,94;,
 3;97,67,96;,
 3;96,67,66;,
 3;68,67,98;,
 3;98,67,97;,
 3;68,98,69;,
 3;69,98,99;,
 3;55,70,54;,
 3;54,70,71;,
 3;100,47,101;,
 3;101,47,54;,
 3;39,47,102;,
 3;102,47,100;,
 3;39,102,31;,
 3;31,102,103;,
 3;3,31,104;,
 3;104,31,103;,
 3;3,104,2;,
 3;2,104,105;,
 3;105,106,2;,
 3;2,106,63;,
 3;19,63,107;,
 3;107,63,106;,
 3;18,19,108;,
 3;108,19,107;,
 3;79,18,109;,
 3;109,18,108;,
 3;110,111,10;,
 3;10,111,8;,
 3;111,112,8;,
 3;8,112,26;,
 3;112,113,26;,
 3;26,113,34;,
 3;113,114,34;,
 3;34,114,42;,
 3;51,42,115;,
 3;115,42,114;,
 3;116,117,86;,
 3;86,117,21;,
 3;23,21,118;,
 3;118,21,117;,
 3;71,23,119;,
 3;119,23,118;,
 3;54,71,101;,
 3;101,71,119;,
 3;85,84,50;,
 3;50,84,43;,
 3;43,84,35;,
 3;35,84,83;,
 3;35,83,27;,
 3;27,83,82;,
 3;27,82,9;,
 3;9,82,80;,
 3;9,80,11;,
 3;11,80,81;,
 3;120,16,121;,
 3;121,16,78;,
 3;122,17,120;,
 3;120,17,16;,
 3;123,62,122;,
 3;122,62,17;,
 3;0,62,93;,
 3;93,62,123;,
 3;1,0,92;,
 3;92,0,93;,
 3;30,1,91;,
 3;91,1,92;,
 3;38,30,90;,
 3;90,30,91;,
 3;46,38,89;,
 3;89,38,90;,
 3;55,46,88;,
 3;88,46,89;,
 3;124,70,88;,
 3;88,70,55;,
 3;125,22,124;,
 3;124,22,70;,
 3;126,20,125;,
 3;125,20,22;,
 3;87,20,127;,
 3;127,20,126;,
 3;128,100,129;,
 3;129,100,101;,
 3;100,128,102;,
 3;102,128,130;,
 3;102,130,103;,
 3;103,130,131;,
 3;103,131,104;,
 3;104,131,132;,
 3;104,132,105;,
 3;105,132,133;,
 3;133,134,105;,
 3;105,134,106;,
 3;107,106,135;,
 3;135,106,134;,
 3;108,107,136;,
 3;136,107,135;,
 3;109,108,137;,
 3;137,108,136;,
 3;111,110,76;,
 3;76,110,77;,
 3;112,111,75;,
 3;75,111,76;,
 3;113,112,74;,
 3;74,112,75;,
 3;114,113,73;,
 3;73,113,74;,
 3;115,114,72;,
 3;72,114,73;,
 3;138,139,116;,
 3;116,139,117;,
 3;118,117,140;,
 3;140,117,139;,
 3;119,118,141;,
 3;141,118,140;,
 3;101,119,129;,
 3;129,119,141;;
 
 MeshMaterialList {
  1;
  224;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.693333;0.508235;0.360784;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  133;
  0.894697;0.000000;0.446674;,
  1.000000;0.000000;0.000000;,
  -0.887419;0.000000;0.460963;,
  -1.000000;0.000000;0.000000;,
  -0.998243;-0.049154;-0.033097;,
  0.894697;0.000000;-0.446674;,
  0.946358;0.017747;0.322631;,
  0.970651;0.023920;-0.239302;,
  -0.970650;0.023920;-0.239302;,
  -0.946358;0.017747;0.322631;,
  0.878923;-0.125979;0.460025;,
  0.930249;-0.125319;-0.344864;,
  -0.930249;-0.125319;-0.344864;,
  -0.878923;-0.125979;0.460025;,
  0.892103;-0.143329;0.428497;,
  0.937354;-0.140414;-0.318829;,
  -0.937354;-0.140414;-0.318829;,
  -0.892103;-0.143329;0.428497;,
  0.775639;-0.130349;0.617570;,
  0.884516;-0.115586;-0.451963;,
  -0.855998;-0.230977;-0.462512;,
  -0.849229;-0.116659;0.514976;,
  -0.961809;-0.273674;-0.005179;,
  -0.973122;-0.230289;0.000000;,
  -0.987749;-0.156049;0.000000;,
  -0.991880;-0.127176;0.000000;,
  -0.999887;0.015023;0.000000;,
  -0.969760;0.244061;0.000000;,
  0.969760;0.244061;0.000000;,
  0.999887;0.015023;0.000000;,
  0.991880;-0.127176;-0.000000;,
  0.987749;-0.156049;-0.000000;,
  0.971314;-0.237801;-0.000000;,
  0.963508;-0.267681;-0.000000;,
  0.978428;-0.177412;-0.105846;,
  0.967059;-0.231529;-0.105785;,
  0.963977;-0.148330;-0.220787;,
  0.983857;-0.133279;-0.119425;,
  0.976067;-0.000527;-0.217469;,
  0.979257;0.182424;-0.088193;,
  -0.979885;0.160963;-0.117971;,
  -0.982496;0.041763;-0.181540;,
  -0.979933;-0.138367;-0.143477;,
  -0.971444;-0.142816;-0.189475;,
  -0.965081;-0.238177;-0.109038;,
  -0.970587;-0.206823;-0.123230;,
  -0.973917;-0.175230;0.144154;,
  -0.961680;-0.233496;0.143706;,
  -0.942106;-0.151612;0.299082;,
  -0.977702;-0.134994;0.160858;,
  -0.955982;-0.005721;0.293370;,
  -0.976265;0.181028;0.118894;,
  0.974407;0.158560;0.159339;,
  0.968753;0.038023;0.245096;,
  0.971026;-0.140300;0.193452;,
  0.955337;-0.145967;0.256953;,
  0.958719;-0.225868;0.172744;,
  0.973988;-0.199410;0.107625;,
  0.000000;-0.647755;0.761848;,
  0.000000;-0.307542;0.951534;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.096542;0.995329;,
  0.000000;-0.239662;0.970857;,
  0.000000;0.928623;0.371023;,
  0.000000;1.000000;0.000000;,
  0.000000;0.956423;-0.291983;,
  0.000000;-0.239662;-0.970856;,
  0.000000;-0.096542;-0.995329;,
  0.000000;0.000000;-1.000000;,
  -0.003385;-0.309973;-0.950739;,
  -0.004671;-0.721275;-0.692633;,
  -0.004450;-0.967733;-0.251940;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.928622;0.371028;,
  -0.058402;-0.628549;-0.775574;,
  -0.253324;-0.294036;-0.921613;,
  -0.084167;-0.022780;-0.996191;,
  0.054020;-0.112368;-0.992197;,
  0.064411;-0.152404;-0.986217;,
  0.000000;0.921949;-0.387311;,
  0.000000;0.948257;0.317503;,
  0.064411;-0.152403;0.986217;,
  0.063027;-0.131106;0.989363;,
  -0.098524;-0.026666;0.994777;,
  -0.206621;-0.186392;0.960503;,
  0.000000;-0.606215;0.795301;,
  0.000000;-0.871512;0.490373;,
  -0.004259;-0.999983;-0.003932;,
  -0.005186;-0.954359;-0.298618;,
  0.000000;-0.627208;0.778852;,
  0.261763;-0.225942;0.938312;,
  0.088177;-0.022836;0.995843;,
  -0.055633;-0.111975;0.992153;,
  -0.044506;0.225709;0.973178;,
  0.000000;0.956423;-0.291983;,
  0.000000;0.681043;-0.732244;,
  -0.064912;-0.130650;-0.989301;,
  0.103253;-0.026740;-0.994296;,
  0.216924;-0.187239;-0.958063;,
  0.000000;-0.690207;-0.723612;,
  0.000000;-0.956422;-0.291987;,
  0.000000;0.829492;-0.558519;,
  0.000000;0.724683;0.689082;,
  0.000000;0.724683;0.689082;,
  -0.098966;-0.226412;-0.968991;,
  0.000000;-0.629864;-0.776706;,
  0.000000;-0.106212;-0.994343;,
  0.000000;-0.052019;-0.998646;,
  0.061361;-0.029061;-0.997693;,
  0.125837;-0.100712;-0.986926;,
  0.000000;0.616809;-0.787113;,
  0.000000;0.981070;-0.193655;,
  0.000000;0.928624;0.371023;,
  0.000000;0.520415;0.853913;,
  0.125837;-0.100712;0.986926;,
  0.061361;-0.029061;0.997693;,
  0.000000;-0.052019;0.998646;,
  0.000000;-0.155634;0.987815;,
  0.000000;-0.661184;0.750224;,
  0.000000;-0.969476;0.245187;,
  0.000000;-0.999956;-0.009349;,
  0.000000;-0.954352;-0.298684;,
  -0.063205;-0.028794;0.997585;,
  -0.129593;-0.099761;0.986536;,
  0.000000;0.394283;0.918989;,
  0.000000;0.871515;0.490368;,
  0.000000;0.616809;-0.787113;,
  -0.129593;-0.099761;-0.986536;,
  -0.063205;-0.028794;-0.997585;,
  0.000000;-0.052019;-0.998646;,
  0.000000;-0.155634;-0.987815;,
  0.000000;-0.690207;-0.723612;,
  0.000000;-0.921947;-0.387315;;
  224;
  3;81,82,62;,
  3;62,82,61;,
  3;40,41,27;,
  3;27,41,26;,
  3;67,77,66;,
  3;66,77,78;,
  3;28,29,39;,
  3;39,29,38;,
  3;79,64,65;,
  3;65,64,64;,
  3;88,71,87;,
  3;87,71,72;,
  3;30,37,29;,
  3;29,37,38;,
  3;67,68,77;,
  3;77,68,68;,
  3;41,42,26;,
  3;26,42,25;,
  3;82,60,61;,
  3;61,60,60;,
  3;30,31,37;,
  3;37,31,36;,
  3;68,76,68;,
  3;68,76,68;,
  3;42,43,25;,
  3;25,43,24;,
  3;60,83,60;,
  3;60,83,60;,
  3;32,35,31;,
  3;31,35,36;,
  3;68,69,76;,
  3;76,69,75;,
  3;43,44,24;,
  3;24,44,23;,
  3;83,84,60;,
  3;60,84,59;,
  3;34,35,33;,
  3;33,35,32;,
  3;75,69,74;,
  3;74,69,70;,
  3;23,44,22;,
  3;22,44,45;,
  3;58,59,85;,
  3;85,59,84;,
  3;46,47,22;,
  3;22,47,23;,
  3;23,47,24;,
  3;24,47,48;,
  3;25,24,49;,
  3;49,24,48;,
  3;25,49,26;,
  3;26,49,50;,
  3;27,26,51;,
  3;51,26,50;,
  3;64,80,64;,
  3;64,80,63;,
  3;52,53,28;,
  3;28,53,29;,
  3;53,54,29;,
  3;29,54,30;,
  3;54,55,30;,
  3;30,55,31;,
  3;55,56,31;,
  3;31,56,32;,
  3;33,32,57;,
  3;57,32,56;,
  3;86,87,73;,
  3;73,87,72;,
  3;5,19,34;,
  3;34,19,35;,
  3;35,19,36;,
  3;36,19,15;,
  3;37,36,11;,
  3;11,36,15;,
  3;37,11,38;,
  3;38,11,7;,
  3;38,7,39;,
  3;39,7,1;,
  3;101,79,101;,
  3;101,79,65;,
  3;41,40,8;,
  3;8,40,3;,
  3;42,41,12;,
  3;12,41,8;,
  3;16,43,12;,
  3;12,43,42;,
  3;44,43,20;,
  3;20,43,16;,
  3;44,20,45;,
  3;45,20,4;,
  3;70,71,74;,
  3;74,71,88;,
  3;2,21,46;,
  3;46,21,47;,
  3;47,21,48;,
  3;48,21,17;,
  3;49,48,13;,
  3;13,48,17;,
  3;49,13,50;,
  3;50,13,9;,
  3;50,9,51;,
  3;51,9,3;,
  3;102,63,103;,
  3;103,63,80;,
  3;53,52,6;,
  3;6,52,1;,
  3;54,53,10;,
  3;10,53,6;,
  3;14,55,10;,
  3;10,55,54;,
  3;56,55,18;,
  3;18,55,14;,
  3;56,18,57;,
  3;57,18,0;,
  3;85,86,58;,
  3;58,86,73;,
  3;90,59,89;,
  3;89,59,58;,
  3;60,59,91;,
  3;91,59,90;,
  3;60,91,60;,
  3;60,91,60;,
  3;61,60,92;,
  3;92,60,60;,
  3;61,92,62;,
  3;62,92,93;,
  3;103,63,102;,
  3;102,63,63;,
  3;64,63,64;,
  3;64,63,63;,
  3;65,64,94;,
  3;94,64,64;,
  3;101,65,95;,
  3;95,65,94;,
  3;104,96,66;,
  3;66,96,67;,
  3;96,68,67;,
  3;67,68,68;,
  3;68,97,68;,
  3;68,97,68;,
  3;97,98,68;,
  3;68,98,69;,
  3;70,69,99;,
  3;99,69,98;,
  3;99,100,70;,
  3;70,100,71;,
  3;72,71,72;,
  3;72,71,100;,
  3;73,72,73;,
  3;73,72,72;,
  3;58,73,89;,
  3;89,73,73;,
  3;105,106,74;,
  3;74,20,75;,
  3;75,20,76;,
  3;76,106,107;,
  3;76,107,68;,
  3;68,107,108;,
  3;68,108,77;,
  3;77,108,109;,
  3;77,109,78;,
  3;78,109,110;,
  3;111,79,110;,
  3;110,79,101;,
  3;64,64,111;,
  3;111,64,79;,
  3;112,80,64;,
  3;64,80,64;,
  3;103,80,113;,
  3;113,80,112;,
  3;82,81,114;,
  3;114,81,113;,
  3;60,82,115;,
  3;115,82,114;,
  3;83,60,116;,
  3;116,60,115;,
  3;84,83,21;,
  3;117,83,116;,
  3;85,84,118;,
  3;2,84,21;,
  3;119,86,118;,
  3;118,86,85;,
  3;120,87,119;,
  3;119,87,86;,
  3;121,88,120;,
  3;120,88,87;,
  3;74,88,105;,
  3;105,88,121;,
  3;18,90,0;,
  3;118,90,89;,
  3;90,18,91;,
  3;91,18,116;,
  3;91,116,60;,
  3;60,116,122;,
  3;60,122,92;,
  3;92,122,123;,
  3;92,123,93;,
  3;93,123,124;,
  3;124,125,93;,
  3;93,125,63;,
  3;64,63,64;,
  3;64,63,125;,
  3;94,64,111;,
  3;111,64,64;,
  3;95,94,126;,
  3;126,94,111;,
  3;96,104,127;,
  3;127,95,126;,
  3;68,96,128;,
  3;128,96,127;,
  3;97,68,129;,
  3;129,68,128;,
  3;98,97,19;,
  3;130,97,129;,
  3;99,98,131;,
  3;5,98,19;,
  3;131,132,99;,
  3;99,132,100;,
  3;72,100,72;,
  3;72,100,132;,
  3;73,72,119;,
  3;119,72,72;,
  3;89,73,118;,
  3;118,73,119;;
 }
 MeshTextureCoords {
  142;
  0.625000;0.179350;,
  0.581900;0.179350;,
  0.625000;0.120830;,
  0.581900;0.120830;,
  0.625000;0.435690;,
  0.581900;0.435690;,
  0.625000;0.367500;,
  0.581900;0.367500;,
  0.581900;0.629170;,
  0.581900;0.570650;,
  0.625000;0.629170;,
  0.625000;0.570650;,
  0.625000;0.882500;,
  0.581900;0.882500;,
  0.625000;0.814310;,
  0.581900;0.814310;,
  0.810690;0.179350;,
  0.742500;0.179350;,
  0.810690;0.120830;,
  0.742500;0.120830;,
  0.189310;0.179350;,
  0.189310;0.120830;,
  0.257500;0.179350;,
  0.257500;0.120830;,
  0.525640;0.882500;,
  0.525640;0.814310;,
  0.525640;0.629170;,
  0.525640;0.570650;,
  0.525640;0.435690;,
  0.525640;0.367500;,
  0.525640;0.179350;,
  0.525640;0.120830;,
  0.467740;0.882500;,
  0.467740;0.814310;,
  0.467740;0.629170;,
  0.467740;0.570650;,
  0.467740;0.435690;,
  0.467740;0.367500;,
  0.467740;0.179350;,
  0.467740;0.120830;,
  0.409850;0.882500;,
  0.409850;0.814310;,
  0.409850;0.629170;,
  0.409850;0.570650;,
  0.409850;0.435690;,
  0.409850;0.367500;,
  0.409850;0.179350;,
  0.409850;0.120830;,
  0.375000;0.814310;,
  0.375000;0.882500;,
  0.375000;0.570650;,
  0.375000;0.629170;,
  0.375000;0.367500;,
  0.375000;0.435690;,
  0.375000;0.120830;,
  0.375000;0.179350;,
  0.375000;0.295540;,
  0.409850;0.295540;,
  0.467740;0.295540;,
  0.525640;0.295540;,
  0.581900;0.295540;,
  0.625000;0.295540;,
  0.670540;0.179350;,
  0.670540;0.120830;,
  0.625000;0.954460;,
  0.581900;0.954460;,
  0.525640;0.954460;,
  0.467740;0.954460;,
  0.409850;0.954460;,
  0.375000;0.954460;,
  0.329460;0.179350;,
  0.329460;0.120830;,
  0.375000;0.750000;,
  0.409850;0.750000;,
  0.467740;0.750000;,
  0.525640;0.750000;,
  0.581900;0.750000;,
  0.625000;0.750000;,
  0.875000;0.179350;,
  0.875000;0.120830;,
  0.581900;0.500000;,
  0.625000;0.500000;,
  0.525640;0.500000;,
  0.467740;0.500000;,
  0.409850;0.500000;,
  0.375000;0.500000;,
  0.125000;0.120830;,
  0.125000;0.179350;,
  0.375000;0.250000;,
  0.409850;0.250000;,
  0.467740;0.250000;,
  0.525640;0.250000;,
  0.581900;0.250000;,
  0.625000;0.250000;,
  0.581900;1.000000;,
  0.625000;1.000000;,
  0.525640;1.000000;,
  0.467740;1.000000;,
  0.409850;1.000000;,
  0.375000;1.000000;,
  0.409850;0.067960;,
  0.375000;0.067960;,
  0.467740;0.067960;,
  0.525640;0.067960;,
  0.581900;0.067960;,
  0.625000;0.067960;,
  0.670540;0.067960;,
  0.742500;0.067960;,
  0.810690;0.067960;,
  0.875000;0.067960;,
  0.625000;0.682040;,
  0.581900;0.682040;,
  0.525640;0.682040;,
  0.467740;0.682040;,
  0.409850;0.682040;,
  0.375000;0.682040;,
  0.125000;0.067960;,
  0.189310;0.067960;,
  0.257500;0.067960;,
  0.329460;0.067960;,
  0.810690;0.250000;,
  0.875000;0.250000;,
  0.742500;0.250000;,
  0.670540;0.250000;,
  0.329460;0.250000;,
  0.257500;0.250000;,
  0.189310;0.250000;,
  0.125000;0.250000;,
  0.409850;0.000000;,
  0.375000;0.000000;,
  0.467740;0.000000;,
  0.525640;0.000000;,
  0.581900;0.000000;,
  0.625000;0.000000;,
  0.670540;0.000000;,
  0.742500;0.000000;,
  0.810690;0.000000;,
  0.875000;0.000000;,
  0.125000;0.000000;,
  0.189310;0.000000;,
  0.257500;0.000000;,
  0.329460;0.000000;;
 }
}
