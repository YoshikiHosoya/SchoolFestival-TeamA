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
 107;
 0.03564;1.63615;-5.40699;,
 0.03564;-5.94782;-4.55312;,
 -1.80820;-5.94782;-4.55312;,
 -2.16082;1.63615;-5.40699;,
 -2.16082;0.09933;-1.01405;,
 -2.16082;0.09933;1.18242;,
 0.03564;0.09933;1.18242;,
 0.03564;0.09933;-1.01405;,
 0.03564;-5.94782;4.37673;,
 0.03564;0.09933;5.28885;,
 -2.16082;0.09933;5.28885;,
 -1.80820;-5.94782;4.37673;,
 -2.16082;-12.59003;1.18242;,
 -2.16082;-12.59003;-1.01405;,
 0.03564;-12.59003;-1.01405;,
 0.03564;-12.59003;1.18242;,
 -4.35730;0.09933;-1.01405;,
 -3.65205;-5.94782;-0.86541;,
 -3.65205;-5.94782;0.97843;,
 -4.35730;0.09933;1.18242;,
 4.42859;0.09933;1.18242;,
 3.72335;-5.94782;0.97843;,
 3.72335;-5.94782;-0.86541;,
 4.42859;0.09933;-1.01405;,
 0.03564;-7.91657;-10.73294;,
 -2.16082;-7.91657;-9.32114;,
 -4.35730;-7.91657;-1.01405;,
 -4.35730;-7.91657;1.18242;,
 0.03564;-7.91657;4.94383;,
 -2.16082;-7.91657;4.94383;,
 4.42859;-7.91657;1.18242;,
 4.42859;-7.91657;-1.01405;,
 0.03564;-12.59003;-10.73294;,
 -2.16082;-12.59003;-9.32114;,
 -4.35730;-12.59003;-1.01405;,
 -4.35730;-12.59003;1.18242;,
 0.03564;-12.59003;5.28885;,
 -2.16082;-12.59003;5.28885;,
 4.42859;-12.59003;1.18242;,
 4.42859;-12.59003;-1.01405;,
 2.23212;-12.59003;-1.01405;,
 2.23212;-12.59003;1.18242;,
 2.23212;-12.59003;5.28885;,
 2.23212;-7.91657;4.94383;,
 1.87950;-5.94782;4.37673;,
 2.23212;0.09933;5.28885;,
 2.23212;0.09933;1.18242;,
 2.23212;0.09933;-1.01405;,
 2.23212;1.63615;-5.40699;,
 1.87950;-5.94782;-4.55312;,
 2.23212;-7.91657;-9.32114;,
 2.23212;-12.59003;-9.32114;,
 2.23212;0.09933;-3.21053;,
 0.03564;0.09933;-3.21053;,
 -2.16082;0.09933;-3.21053;,
 -4.35730;0.09933;-3.21053;,
 -3.65205;-5.94782;-2.70926;,
 -4.35730;-7.91657;-3.21053;,
 -4.35730;-12.59003;-3.21053;,
 -2.16082;-12.59003;-3.21053;,
 0.03564;-12.59003;-3.21053;,
 2.23212;-12.59003;-3.21053;,
 4.42859;-12.59003;-3.21053;,
 4.42859;-7.91657;-3.21053;,
 3.72335;-5.94782;-2.70926;,
 4.42859;0.09933;-3.21053;,
 -3.65205;-5.94782;-3.40605;,
 -4.35730;0.09933;-4.04057;,
 -4.35730;-7.91657;-6.48930;,
 -4.35730;-12.59003;-6.48930;,
 0.03564;-12.59003;-10.73294;,
 -2.16082;-12.59003;-9.32114;,
 2.23212;-12.59003;-9.32114;,
 4.42859;-12.59003;-6.48930;,
 4.42859;-7.91657;-6.48930;,
 3.72335;-5.94782;-3.40605;,
 4.42859;0.09933;-4.04057;,
 -4.35730;-12.59003;3.37890;,
 -4.35730;-7.91657;3.37890;,
 -3.65205;-5.94782;2.82228;,
 -4.35730;0.09933;3.37890;,
 3.72335;-5.94782;2.82228;,
 4.42859;0.09933;3.37890;,
 4.42859;-7.91657;3.37890;,
 4.42859;-12.59003;3.37890;,
 4.42859;-12.59003;-3.21053;,
 4.42859;-12.59003;-6.48930;,
 4.42859;-12.59003;-1.01405;,
 4.42859;-12.59003;1.18242;,
 4.42859;-12.59003;3.37890;,
 4.42859;-7.91657;3.37890;,
 3.72335;-5.94782;2.82228;,
 4.42859;0.09933;3.37890;,
 4.42859;0.09933;1.18242;,
 4.42859;0.09933;-1.01405;,
 4.42859;0.09933;-3.21053;,
 -3.65205;-5.94782;2.82228;,
 -4.35730;-7.91657;3.37890;,
 -4.35730;-12.59003;3.37890;,
 -4.35730;-12.59003;1.18242;,
 -4.35730;-12.59003;-1.01405;,
 -4.35730;-12.59003;-3.21053;,
 -4.35730;-12.59003;-6.48930;,
 -4.35730;0.09933;-3.21053;,
 -4.35730;0.09933;-1.01405;,
 -4.35730;0.09933;1.18242;,
 -4.35730;0.09933;3.37890;;
 
 80;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;1,24,25,2;,
 4;17,26,27,18;,
 4;28,8,11,29;,
 4;21,30,31,22;,
 4;24,32,33,25;,
 4;26,34,35,27;,
 4;36,28,29,37;,
 4;30,38,39,31;,
 4;40,41,15,14;,
 4;42,43,28,36;,
 4;43,44,8,28;,
 4;44,45,9,8;,
 4;46,47,7,6;,
 4;48,49,1,0;,
 4;49,50,24,1;,
 4;50,51,32,24;,
 4;47,52,53,7;,
 4;54,4,7,53;,
 4;55,56,17,16;,
 4;56,57,26,17;,
 4;57,58,34,26;,
 4;13,59,60,14;,
 4;61,40,14,60;,
 4;31,39,62,63;,
 4;22,31,63,64;,
 4;23,22,64,65;,
 4;52,48,0,53;,
 4;3,54,53,0;,
 4;66,56,55,67;,
 4;68,57,56,66;,
 4;69,58,57,68;,
 4;70,60,59,71;,
 4;72,61,60,70;,
 4;63,62,73,74;,
 4;64,63,74,75;,
 4;65,64,75,76;,
 4;41,42,36,15;,
 4;37,12,15,36;,
 4;27,35,77,78;,
 4;18,27,78,79;,
 4;19,18,79,80;,
 4;9,6,5,10;,
 4;45,46,6,9;,
 4;81,21,20,82;,
 4;83,30,21,81;,
 4;84,38,30,83;,
 4;85,61,72,86;,
 4;87,40,61,85;,
 4;88,41,40,87;,
 4;89,42,41,88;,
 4;90,43,42,89;,
 4;91,44,43,90;,
 4;92,45,44,91;,
 4;93,46,45,92;,
 4;94,47,46,93;,
 4;95,52,47,94;,
 4;76,48,52,95;,
 4;75,49,48,76;,
 4;74,50,49,75;,
 4;73,51,50,74;,
 4;29,11,96,97;,
 4;37,29,97,98;,
 4;99,12,37,98;,
 4;100,13,12,99;,
 4;101,59,13,100;,
 4;71,59,101,102;,
 4;25,33,69,68;,
 4;2,25,68,66;,
 4;3,2,66,67;,
 4;103,54,3,67;,
 4;104,4,54,103;,
 4;105,5,4,104;,
 4;10,5,105,106;,
 4;11,10,106,96;;
 
 MeshMaterialList {
  11;
  80;
  1,
  1,
  1,
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
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
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
  1,
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
  1,
  1,
  1,
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
  1,
  1,
  1,
  0;;
  Material {
   0.160000;0.160000;0.160000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.357647;0.000000;0.326275;1.000000;;
   5.000000;
   0.810000;0.810000;0.810000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.671373;0.467451;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.240000;0.240000;0.240000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.116078;0.116078;0.116078;1.000000;;
   5.000000;
   0.880000;0.880000;0.880000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.442353;0.006275;0.000000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.423529;0.338824;0.495686;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.263529;0.015686;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.517647;0.517647;0.517647;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.172549;0.112941;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.727843;0.238431;1.000000;;
   25.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  65;
  0.946090;0.000000;-0.323904;,
  -0.946090;0.000000;-0.323905;,
  0.993268;-0.115838;-0.000000;,
  -0.993268;-0.115841;0.000000;,
  0.899261;-0.144533;0.412843;,
  -0.899261;-0.144535;0.412844;,
  0.899631;0.015481;0.436376;,
  -0.899631;0.015481;0.436377;,
  0.993516;0.113692;0.000000;,
  -0.993516;0.113694;0.000000;,
  -0.897253;0.123778;0.423811;,
  0.897254;0.123777;0.423810;,
  0.968738;0.119597;-0.217354;,
  -0.892893;0.342829;-0.291909;,
  -0.880560;0.203945;0.427810;,
  0.880561;0.203942;0.427809;,
  -0.540700;0.000000;-0.841216;,
  0.000000;0.073624;0.997286;,
  0.000000;0.176152;0.984363;,
  0.000000;0.065331;0.997864;,
  0.000000;-0.149148;0.988815;,
  0.000000;-0.111883;-0.993721;,
  -0.000000;0.939240;-0.343261;,
  0.993268;-0.115838;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.993268;-0.115841;0.000000;,
  -0.985246;0.171145;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.985247;0.171141;0.000000;,
  0.993516;0.113692;0.000000;,
  0.000000;0.953770;0.300537;,
  -0.993268;-0.115841;0.000000;,
  -0.993516;0.113694;0.000000;,
  -0.993516;0.113694;0.000000;,
  0.993516;0.113692;0.000000;,
  0.675158;0.000000;-0.737674;,
  0.327429;0.053707;0.943348;,
  0.317444;0.196891;0.927611;,
  0.331917;0.093068;0.938706;,
  0.342404;-0.157733;0.926218;,
  0.028839;0.974047;0.224502;,
  0.254797;-0.127583;-0.958541;,
  0.227257;0.899843;-0.372339;,
  -0.331917;0.093068;0.938706;,
  -0.317443;0.196892;0.927612;,
  -0.327428;0.053707;0.943349;,
  -0.675157;0.000000;-0.737674;,
  -0.227256;0.899843;-0.372339;,
  -0.254796;-0.127583;-0.958541;,
  -0.028839;0.974047;0.224502;,
  -0.342403;-0.157734;0.926218;,
  0.540697;0.000000;-0.841217;,
  0.056542;0.896136;0.440162;,
  0.000000;0.819355;0.573287;,
  -0.056542;0.896136;0.440162;,
  0.056511;0.987139;0.149540;,
  0.111569;0.948888;0.295234;,
  0.492673;-0.134811;-0.859709;,
  0.353846;0.847420;-0.395817;,
  -0.353845;0.847421;-0.395817;,
  -0.492672;-0.134812;-0.859709;,
  -0.056511;0.987139;0.149540;,
  -0.111568;0.948888;0.295234;;
  80;
  4;21,21,50,50;,
  4;24,24,24,24;,
  4;19,20,52,45;,
  4;28,28,28,28;,
  4;25,9,35,25;,
  4;23,36,31,23;,
  4;22,22,49,49;,
  4;9,26,26,35;,
  4;18,19,45,46;,
  4;36,30,30,31;,
  4;16,16,48,48;,
  4;26,27,27,26;,
  4;17,18,46,47;,
  4;30,29,29,30;,
  4;28,28,28,28;,
  4;38,39,18,17;,
  4;39,40,19,18;,
  4;40,41,20,19;,
  4;24,24,24,24;,
  4;43,43,21,21;,
  4;44,44,22,22;,
  4;37,37,53,53;,
  4;24,42,32,24;,
  4;51,24,24,32;,
  4;33,34,9,25;,
  4;34,26,26,9;,
  4;26,27,27,26;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;30,29,29,30;,
  4;31,30,30,31;,
  4;23,31,31,23;,
  4;42,54,55,32;,
  4;56,51,32,55;,
  4;9,34,33,3;,
  4;13,26,34,9;,
  4;1,27,26,13;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;30,29,0,12;,
  4;31,30,12,8;,
  4;23,31,8,2;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;26,27,7,14;,
  4;35,26,14,10;,
  4;25,35,10,5;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;11,36,23,4;,
  4;15,30,36,11;,
  4;6,29,30,15;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;15,39,38,6;,
  4;11,40,39,15;,
  4;4,41,40,11;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;57,42,24,24;,
  4;58,54,42,57;,
  4;59,43,43,59;,
  4;60,44,44,60;,
  4;0,37,37,12;,
  4;46,45,10,14;,
  4;47,46,14,7;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;48,48,1,13;,
  4;49,49,13,61;,
  4;50,50,62,62;,
  4;63,51,56,64;,
  4;24,24,51,63;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;45,52,5,10;;
 }
 MeshTextureCoords {
  107;
  0.500000;0.250000;,
  0.500000;0.130862;,
  0.562500;0.130862;,
  0.562500;0.250000;,
  0.562500;0.375000;,
  0.562500;0.437500;,
  0.500000;0.437500;,
  0.500000;0.375000;,
  0.500000;0.619138;,
  0.500000;0.500000;,
  0.562500;0.500000;,
  0.562500;0.619138;,
  0.562500;0.812500;,
  0.562500;0.875000;,
  0.500000;0.875000;,
  0.500000;0.812500;,
  0.750000;0.250000;,
  0.750000;0.130862;,
  0.812500;0.130862;,
  0.812500;0.250000;,
  0.187500;0.250000;,
  0.187500;0.130862;,
  0.250000;0.130862;,
  0.250000;0.250000;,
  0.500000;0.092074;,
  0.562500;0.092074;,
  0.750000;0.092074;,
  0.812500;0.092074;,
  0.500000;0.657926;,
  0.562500;0.657926;,
  0.187500;0.092074;,
  0.250000;0.092074;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.500000;0.750000;,
  0.562500;0.750000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.437500;0.875000;,
  0.437500;0.812500;,
  0.437500;0.750000;,
  0.437500;0.657926;,
  0.437500;0.619138;,
  0.437500;0.500000;,
  0.437500;0.437500;,
  0.437500;0.375000;,
  0.437500;0.250000;,
  0.437500;0.130862;,
  0.437500;0.092074;,
  0.437500;0.000000;,
  0.437500;0.312500;,
  0.500000;0.312500;,
  0.562500;0.312500;,
  0.687500;0.250000;,
  0.687500;0.130862;,
  0.687500;0.092074;,
  0.687500;0.000000;,
  0.562500;0.937500;,
  0.500000;0.937500;,
  0.437500;0.937500;,
  0.312500;0.000000;,
  0.312500;0.092074;,
  0.312500;0.130862;,
  0.312500;0.250000;,
  0.625000;0.130862;,
  0.625000;0.250000;,
  0.625000;0.092074;,
  0.625000;0.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.437500;1.000000;,
  0.375000;0.000000;,
  0.375000;0.092074;,
  0.375000;0.130862;,
  0.375000;0.250000;,
  0.875000;0.000000;,
  0.875000;0.092074;,
  0.875000;0.130862;,
  0.875000;0.250000;,
  0.125000;0.130862;,
  0.125000;0.250000;,
  0.125000;0.092074;,
  0.125000;0.000000;,
  0.375000;0.937500;,
  0.375000;1.000000;,
  0.375000;0.875000;,
  0.375000;0.812500;,
  0.375000;0.750000;,
  0.375000;0.657926;,
  0.375000;0.619138;,
  0.375000;0.500000;,
  0.375000;0.437500;,
  0.375000;0.375000;,
  0.375000;0.312500;,
  0.625000;0.619138;,
  0.625000;0.657926;,
  0.625000;0.750000;,
  0.625000;0.812500;,
  0.625000;0.875000;,
  0.625000;0.937500;,
  0.625000;1.000000;,
  0.625000;0.312500;,
  0.625000;0.375000;,
  0.625000;0.437500;,
  0.625000;0.500000;;
 }
}
