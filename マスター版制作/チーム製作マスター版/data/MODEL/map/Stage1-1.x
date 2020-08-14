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
 136;
 7942.60840;53.74525;-119.02280;,
 7947.94629;53.74525;142.35339;,
 7947.94629;-1209.05396;142.35339;,
 7942.60840;-1209.05396;-188.93045;,
 -844.56689;66.46130;142.35339;,
 -849.89502;66.46130;-119.02280;,
 -846.71234;-1209.05396;-188.81551;,
 -841.37988;-1209.05396;142.46815;,
 6775.72510;44.12020;-119.02280;,
 6775.72510;-1205.46143;-188.93045;,
 6707.05811;-1205.46143;-188.93045;,
 6707.05811;42.53030;-119.02280;,
 6712.39062;42.53030;142.35339;,
 6781.05713;44.12020;142.35339;,
 6781.05713;-1205.46143;142.35339;,
 6712.39062;-1205.46143;142.35339;,
 6847.37012;44.83840;-119.02280;,
 6847.37012;-1205.46143;-188.93045;,
 6852.70068;44.83840;142.35339;,
 6852.70068;-1205.46143;142.35339;,
 6915.86084;45.36935;-119.02280;,
 6915.86084;-1205.46143;-188.93045;,
 6921.19287;45.36935;142.35339;,
 6921.19287;-1205.46143;142.35339;,
 7002.49805;48.36605;-119.02280;,
 7002.49805;-1205.46143;-188.93045;,
 7007.83105;48.36605;142.35339;,
 7007.83105;-1205.46143;142.35339;,
 7087.83350;47.20370;-119.02280;,
 7087.83350;-1205.46143;-188.93045;,
 7093.16309;47.20370;142.35339;,
 7093.16309;-1205.46143;142.35339;,
 7169.43555;47.67595;-119.02280;,
 7169.43555;-1205.46143;-188.93045;,
 7174.77148;47.67595;142.35339;,
 7174.77148;-1205.46143;142.35339;,
 6199.65137;-1209.05396;-188.93045;,
 6199.65137;55.61035;-119.02280;,
 6204.98047;56.00025;142.35339;,
 6204.98047;-1209.05396;142.35339;,
 7302.56396;49.55105;-119.02280;,
 7302.56396;-1205.46143;-188.93045;,
 7307.89404;49.55105;142.35339;,
 7307.89404;-1205.46143;142.35339;,
 7943.15332;58.12560;152.69370;,
 7939.75146;58.12560;-126.97870;,
 7939.75146;-1206.25879;-200.39005;,
 7943.15332;-1206.25879;152.69370;,
 8811.73340;58.12560;152.55940;,
 8811.73340;-1206.25879;152.55940;,
 8807.50000;58.12560;-126.97870;,
 8807.01074;-1206.25879;-200.39005;,
 474.30319;196.17316;-60.63860;,
 725.91455;196.17316;-60.63860;,
 725.91455;172.51375;-85.23830;,
 474.30319;172.51375;-85.23830;,
 725.91455;196.17316;146.08685;,
 725.91455;172.51375;146.08685;,
 474.30319;196.17316;146.08685;,
 474.30319;172.51375;146.08685;,
 1024.41406;195.88934;-61.13950;,
 1276.01978;195.88934;-61.13950;,
 1276.01978;175.00349;-85.73920;,
 1024.41406;175.00349;-85.73920;,
 1276.01978;195.88934;140.76939;,
 1276.01978;175.00349;140.76939;,
 1024.41406;195.88934;140.76939;,
 1024.41406;175.00349;140.76939;,
 1636.34131;188.90926;-61.13950;,
 1887.94775;188.90926;-61.13950;,
 1887.94775;168.02319;-85.73920;,
 1636.34131;168.02319;-85.73920;,
 1887.94775;188.90926;140.76939;,
 1887.94775;168.02319;140.76939;,
 1636.34131;188.90926;140.76939;,
 1636.34131;168.02319;140.76939;,
 3089.93506;188.90926;-61.13950;,
 3341.54053;188.90926;-61.13950;,
 3341.54053;168.02319;-85.73920;,
 3089.93506;168.02319;-85.73920;,
 3341.54053;188.90926;140.76939;,
 3341.54053;168.02319;140.76939;,
 3089.93506;188.90926;140.76939;,
 3089.93506;168.02319;140.76939;,
 4640.05762;302.36841;-61.13950;,
 5578.83398;302.36841;-61.13950;,
 5578.83398;271.45929;-85.73920;,
 4640.05762;271.45929;-85.73920;,
 5578.83398;302.36841;140.76939;,
 5578.83398;271.45929;140.76939;,
 4640.05762;302.36841;140.76939;,
 4640.05762;271.45929;140.76939;,
 5665.62598;188.90926;-61.13950;,
 5917.23145;188.90926;-61.13950;,
 5917.23145;168.02319;-85.73920;,
 5665.62598;168.02319;-85.73920;,
 5917.23145;188.90926;140.76939;,
 5917.23145;168.02319;140.76939;,
 5665.62598;188.90926;140.76939;,
 5665.62598;168.02319;140.76939;,
 3410.95581;302.36841;-61.13950;,
 4349.72656;302.36841;-61.13950;,
 4349.72656;271.45929;-85.73920;,
 3410.95581;271.45929;-85.73920;,
 4349.72656;302.36841;140.76939;,
 4349.72656;271.45929;140.76939;,
 3410.95581;302.36841;140.76939;,
 3410.95581;271.45929;140.76939;,
 3089.93506;188.90926;-61.13950;,
 3341.54053;188.90926;-61.13950;,
 3341.54053;168.02319;-85.73920;,
 3089.93506;168.02319;-85.73920;,
 3341.54053;188.90926;140.76939;,
 3341.54053;168.02319;140.76939;,
 3089.93506;188.90926;140.76939;,
 3089.93506;168.02319;140.76939;,
 -1750.60742;950.59747;216.23105;,
 9614.95508;950.59747;216.23105;,
 9614.95508;-1285.32129;216.23105;,
 -1750.60742;-1285.32129;216.23105;,
 4369.08350;188.90926;-61.13950;,
 4620.68896;188.90926;-61.13950;,
 4620.68896;168.02319;-85.73920;,
 4369.08350;168.02319;-85.73920;,
 4620.68896;188.90926;140.76939;,
 4620.68896;168.02319;140.76939;,
 4369.08350;188.90926;140.76939;,
 4369.08350;168.02319;140.76939;,
 1986.90259;302.36841;-61.13950;,
 2925.67358;302.36841;-61.13950;,
 2925.67358;271.45929;-85.73920;,
 1986.90259;271.45929;-85.73920;,
 2925.67358;302.36841;140.76939;,
 2925.67358;271.45929;140.76939;,
 1986.90259;302.36841;140.76939;,
 1986.90259;271.45929;140.76939;;
 
 110;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;9,14,15,10;,
 4;13,12,15,14;,
 4;16,17,9,8;,
 4;16,8,13,18;,
 4;17,19,14,9;,
 4;18,13,14,19;,
 4;20,21,17,16;,
 4;20,16,18,22;,
 4;21,23,19,17;,
 4;22,18,19,23;,
 4;24,25,21,20;,
 4;24,20,22,26;,
 4;25,27,23,21;,
 4;26,22,23,27;,
 4;28,29,25,24;,
 4;28,24,26,30;,
 4;29,31,27,25;,
 4;30,26,27,31;,
 4;32,33,29,28;,
 4;32,28,30,34;,
 4;33,35,31,29;,
 4;34,30,31,35;,
 4;36,37,11,10;,
 4;37,38,12,11;,
 4;39,36,10,15;,
 4;38,39,15,12;,
 4;40,41,33,32;,
 4;40,32,34,42;,
 4;41,43,35,33;,
 4;42,34,35,43;,
 4;44,45,46,47;,
 4;41,40,0,3;,
 4;40,42,1,0;,
 4;43,41,3,2;,
 4;42,43,2,1;,
 4;37,36,6,5;,
 4;38,37,5,4;,
 4;36,39,7,6;,
 4;39,38,4,7;,
 4;48,44,47,49;,
 4;48,50,45,44;,
 4;49,47,46,51;,
 4;50,51,46,45;,
 4;52,53,54,55;,
 4;53,56,57,54;,
 4;56,58,59,57;,
 4;58,52,55,59;,
 4;58,56,53,52;,
 4;55,54,57,59;,
 4;60,61,62,63;,
 4;61,64,65,62;,
 4;64,66,67,65;,
 4;66,60,63,67;,
 4;66,64,61,60;,
 4;63,62,65,67;,
 4;68,69,70,71;,
 4;69,72,73,70;,
 4;72,74,75,73;,
 4;74,68,71,75;,
 4;74,72,69,68;,
 4;71,70,73,75;,
 4;76,77,78,79;,
 4;77,80,81,78;,
 4;80,82,83,81;,
 4;82,76,79,83;,
 4;82,80,77,76;,
 4;79,78,81,83;,
 4;84,85,86,87;,
 4;85,88,89,86;,
 4;88,90,91,89;,
 4;90,84,87,91;,
 4;90,88,85,84;,
 4;87,86,89,91;,
 4;92,93,94,95;,
 4;93,96,97,94;,
 4;96,98,99,97;,
 4;98,92,95,99;,
 4;98,96,93,92;,
 4;95,94,97,99;,
 4;100,101,102,103;,
 4;101,104,105,102;,
 4;104,106,107,105;,
 4;106,100,103,107;,
 4;106,104,101,100;,
 4;103,102,105,107;,
 4;108,109,110,111;,
 4;109,112,113,110;,
 4;112,114,115,113;,
 4;114,108,111,115;,
 4;114,112,109,108;,
 4;111,110,113,115;,
 4;48,49,51,50;,
 4;50,51,49,48;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;121,124,125,122;,
 4;124,126,127,125;,
 4;126,120,123,127;,
 4;126,124,121,120;,
 4;123,122,125,127;,
 4;128,129,130,131;,
 4;129,132,133,130;,
 4;132,134,135,133;,
 4;134,128,131,135;,
 4;134,132,129,128;,
 4;131,130,133,135;;
 
 MeshMaterialList {
  7;
  110;
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  1,
  0,
  2,
  0,
  1,
  0,
  2,
  0,
  1,
  0,
  2,
  0,
  1,
  0,
  2,
  0,
  1,
  0,
  2,
  0,
  1,
  0,
  2,
  0,
  1,
  0,
  2,
  0,
  0,
  1,
  0,
  2,
  0,
  1,
  0,
  2,
  2,
  1,
  0,
  0,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  2,
  2,
  4,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5;;
  Material {
   0.480000;0.480000;0.480000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\materialtexture\\OIP.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\materialtexture\\OIP.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\materialtexture\\OIP.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.599200;0.135200;1.000000;;
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
  -0.999829;-0.002936;0.018237;,
  0.999833;0.000446;-0.018264;,
  0.000280;0.055238;-0.998473;,
  0.013834;0.999904;-0.001028;,
  0.003540;-0.999994;-0.000057;,
  -0.000061;0.055727;-0.998446;,
  0.001503;0.999999;-0.000404;,
  -0.000464;0.055867;-0.998438;,
  -0.016586;0.999862;0.000338;,
  0.000000;-1.000000;-0.000000;,
  -0.000248;0.055828;-0.998440;,
  -0.008888;0.999961;0.000181;,
  -0.000590;0.055775;-0.998443;,
  -0.021162;0.999776;0.000432;,
  -0.000292;0.055715;-0.998447;,
  -0.010477;0.999945;0.000214;,
  0.000109;0.055702;-0.998447;,
  0.003917;0.999992;-0.000080;,
  -0.000276;0.055684;-0.998448;,
  -0.009935;0.999951;0.000203;,
  -0.000208;0.055552;-0.998456;,
  -0.010318;0.999947;0.000211;,
  -0.002806;-0.999996;0.000045;,
  -0.999941;-0.000280;0.010899;,
  0.000155;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.927563;-0.373666;,
  0.000000;0.720747;-0.693198;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.938697;-0.344743;,
  0.000000;0.762305;-0.647218;,
  0.000000;0.938696;-0.344745;,
  0.000000;0.762301;-0.647222;,
  0.000000;0.938696;-0.344745;,
  0.000000;0.762301;-0.647222;,
  0.000000;0.900756;-0.434325;,
  0.000000;0.622724;-0.782442;,
  0.000000;0.000000;-1.000000;,
  0.000004;0.000022;1.000000;,
  -0.000025;0.055446;-0.998462;,
  -0.006553;0.999979;0.000134;,
  -0.005613;-0.999984;0.000090;,
  0.000034;0.054915;-0.998491;,
  0.001512;0.999999;-0.000777;,
  0.000008;0.000045;1.000000;,
  0.000000;0.057963;-0.998319;,
  -1.000000;0.000000;0.000000;,
  0.999898;0.000195;-0.014261;,
  -0.999898;-0.000195;0.014261;,
  0.000000;0.938696;-0.344745;,
  0.000000;0.762301;-0.647222;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.900756;-0.434325;,
  0.000000;0.622724;-0.782442;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  110;
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;7,7,5,5;,
  4;8,6,6,8;,
  4;9,9,4,4;,
  4;29,29,29,29;,
  4;10,10,7,7;,
  4;11,8,8,11;,
  4;9,9,9,9;,
  4;29,29,29,29;,
  4;12,12,10,10;,
  4;13,11,11,13;,
  4;9,9,9,9;,
  4;29,29,29,29;,
  4;14,14,12,12;,
  4;15,13,13,15;,
  4;9,9,9,9;,
  4;29,29,29,29;,
  4;16,16,14,14;,
  4;17,15,15,17;,
  4;9,9,9,9;,
  4;29,29,29,29;,
  4;18,18,16,16;,
  4;19,17,17,19;,
  4;9,9,9,9;,
  4;29,29,29,29;,
  4;2,2,5,5;,
  4;3,3,6,6;,
  4;4,4,4,4;,
  4;39,39,29,29;,
  4;20,20,18,18;,
  4;21,19,19,21;,
  4;22,22,9,9;,
  4;29,29,29,29;,
  4;23,23,23,23;,
  4;20,20,40,40;,
  4;21,21,41,41;,
  4;22,22,42,42;,
  4;29,29,29,29;,
  4;2,2,43,43;,
  4;3,3,44,44;,
  4;4,4,9,9;,
  4;39,39,45,45;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;9,9,9,9;,
  4;46,46,46,46;,
  4;26,26,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;47,47,47,47;,
  4;25,25,26,26;,
  4;9,9,9,9;,
  4;30,30,31,31;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;47,47,47,47;,
  4;25,25,30,30;,
  4;9,9,9,9;,
  4;32,32,33,33;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;47,47,47,47;,
  4;25,25,32,32;,
  4;9,9,9,9;,
  4;34,34,35,35;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;47,47,47,47;,
  4;25,25,34,34;,
  4;9,9,9,9;,
  4;36,36,37,37;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;47,47,47,47;,
  4;25,25,36,36;,
  4;9,9,9,9;,
  4;34,34,35,35;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;47,47,47,47;,
  4;25,25,34,34;,
  4;9,9,9,9;,
  4;36,36,37,37;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;47,47,47,47;,
  4;25,25,36,36;,
  4;9,9,9,9;,
  4;34,34,35,35;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;47,47,47,47;,
  4;25,25,34,34;,
  4;9,9,9,9;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;38,38,38,38;,
  4;50,50,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,50,50;,
  4;56,56,56,56;,
  4;57,57,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,57,57;,
  4;63,63,63,63;;
 }
 MeshTextureCoords {
  136;
  80.912086;-0.037450;,
  80.965469;-0.037450;,
  80.965469;12.590540;,
  80.912086;12.590540;,
  0.693230;-0.164610;,
  0.639950;-0.164610;,
  0.671780;12.590540;,
  0.725100;12.590540;,
  69.243263;-3.003800;,
  69.243263;12.590540;,
  68.556587;12.590540;,
  68.556587;-2.987900;,
  68.609909;-2.987900;,
  69.296577;-3.003800;,
  69.296577;12.590540;,
  68.609909;12.590540;,
  69.959709;-3.010980;,
  69.959709;12.590540;,
  70.013008;-3.010980;,
  70.013008;12.590540;,
  70.644623;-3.016290;,
  70.644623;12.590540;,
  70.697929;-3.016290;,
  70.697929;12.590540;,
  71.510986;-3.046260;,
  71.510986;12.590540;,
  71.564323;-3.046260;,
  71.564323;12.590540;,
  72.364342;-3.034630;,
  72.364342;12.590540;,
  72.417633;-3.034630;,
  72.417633;12.590540;,
  73.180359;-3.039350;,
  73.180359;12.590540;,
  73.233719;-3.039350;,
  73.233719;12.590540;,
  63.482521;12.590540;,
  63.482521;-0.056100;,
  63.535809;-0.060000;,
  63.535809;12.590540;,
  74.511642;-3.058110;,
  74.511642;12.590540;,
  74.564941;-3.058110;,
  74.564941;12.590540;,
  80.917526;-0.081260;,
  80.883522;-0.081260;,
  80.883522;12.562590;,
  80.917526;12.562590;,
  82.050598;-0.081260;,
  82.050598;12.562590;,
  82.008270;-0.081260;,
  82.003380;12.562590;,
  6.229040;-1.941220;,
  8.745150;-1.941220;,
  8.745150;-1.704630;,
  6.229040;-1.704630;,
  8.745150;-1.941220;,
  8.745150;-1.704630;,
  6.229040;-1.941220;,
  6.229040;-1.704630;,
  11.730150;-1.938390;,
  14.246200;-1.938390;,
  14.246200;-1.729530;,
  11.730150;-1.729530;,
  14.246200;-1.938390;,
  14.246200;-1.729530;,
  11.730150;-1.938390;,
  11.730150;-1.729530;,
  17.849421;-1.868580;,
  20.365480;-1.868580;,
  20.365480;-1.659720;,
  17.849421;-1.659720;,
  20.365480;-1.868580;,
  20.365480;-1.659720;,
  17.849421;-1.868580;,
  17.849421;-1.659720;,
  32.385349;-1.868580;,
  34.901409;-1.868580;,
  34.901409;-1.659720;,
  32.385349;-1.659720;,
  34.901409;-1.868580;,
  34.901409;-1.659720;,
  32.385349;-1.868580;,
  32.385349;-1.659720;,
  47.886581;-2.914010;,
  57.274349;-2.914010;,
  57.274349;-2.444080;,
  47.886581;-2.444080;,
  57.274349;-2.914010;,
  57.274349;-2.444080;,
  47.886581;-2.914010;,
  47.886581;-2.444080;,
  58.142269;-1.868580;,
  60.658321;-1.868580;,
  60.658321;-1.659720;,
  58.142269;-1.659720;,
  60.658321;-1.868580;,
  60.658321;-1.659720;,
  58.142269;-1.868580;,
  58.142269;-1.659720;,
  35.595558;-2.914010;,
  44.983269;-2.914010;,
  44.983269;-2.444080;,
  35.595558;-2.444080;,
  44.983269;-2.914010;,
  44.983269;-2.444080;,
  35.595558;-2.914010;,
  35.595558;-2.444080;,
  32.385349;-1.868580;,
  34.901409;-1.868580;,
  34.901409;-1.659720;,
  32.385349;-1.659720;,
  34.901409;-1.868580;,
  34.901409;-1.659720;,
  32.385349;-1.868580;,
  32.385349;-1.659720;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  58.142269;-1.868580;,
  60.658321;-1.868580;,
  60.658321;-1.659720;,
  58.142269;-1.659720;,
  60.658321;-1.868580;,
  60.658321;-1.659720;,
  58.142269;-1.868580;,
  58.142269;-1.659720;,
  35.595558;-2.914010;,
  44.983269;-2.914010;,
  44.983269;-2.444080;,
  35.595558;-2.444080;,
  44.983269;-2.914010;,
  44.983269;-2.444080;,
  35.595558;-2.914010;,
  35.595558;-2.444080;;
 }
}
