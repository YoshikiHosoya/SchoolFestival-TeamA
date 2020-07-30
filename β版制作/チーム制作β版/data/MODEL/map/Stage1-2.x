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
 96;
 1898.43896;58.12560;-126.97870;,
 2135.50342;201.86505;-126.97870;,
 2132.43896;-1206.25879;-200.39005;,
 1894.86279;-1206.25879;-200.39005;,
 1657.28760;-1206.25879;-200.39005;,
 1661.37354;58.12560;-126.97870;,
 1669.19385;58.12560;148.39610;,
 1905.28076;58.12560;148.39610;,
 2141.36865;201.86505;148.39610;,
 2141.36865;-1206.25879;148.39610;,
 1905.28076;-1206.25879;148.39610;,
 1669.19385;-1206.25879;148.39610;,
 2372.56885;201.86505;-126.97870;,
 2609.63428;58.12560;-126.97870;,
 2607.59131;-1206.25879;-200.39005;,
 2370.01514;-1206.25879;-200.39005;,
 2377.45654;201.86505;148.39610;,
 2613.54443;58.12560;148.39610;,
 2613.54443;-1206.25879;148.39610;,
 2377.45654;-1206.25879;148.39610;,
 2846.69971;58.12560;-126.97870;,
 3083.76514;64.97430;-126.97870;,
 3082.74365;-1206.25879;-200.39005;,
 2845.16748;-1206.25879;-200.39005;,
 2849.63232;58.12560;148.39610;,
 3085.72021;64.97430;148.39610;,
 3085.72021;-1206.25879;148.39610;,
 2849.63232;-1206.25879;148.39610;,
 3320.82959;204.90915;-126.97870;,
 3320.31982;-1206.25879;-200.39005;,
 3321.80811;204.90915;148.39610;,
 3321.80811;-1206.25879;148.39610;,
 3546.66260;198.06046;-126.97870;,
 3543.75732;-1206.25879;-200.39005;,
 3551.55615;198.06046;148.39610;,
 3549.95557;-1206.25879;148.39610;,
 1454.74268;63.46885;-126.97870;,
 1449.97412;-1206.25879;-200.39005;,
 1242.66162;-1206.25879;-200.39005;,
 1248.11182;203.40370;-126.97870;,
 1261.21045;203.40370;150.54491;,
 1465.20264;63.46885;149.47050;,
 1465.20264;-1206.25879;149.47050;,
 1261.21045;-1206.25879;150.54491;,
 987.98193;211.62045;-126.97870;,
 984.06689;-1206.25879;-200.39005;,
 998.02783;211.62045;151.61929;,
 998.02783;-1206.25879;151.61929;,
 673.82568;58.12560;-126.97870;,
 671.86865;-1206.25879;-200.39005;,
 680.55029;58.12560;152.15649;,
 680.55029;-1206.25879;152.15649;,
 3750.21240;58.12560;-126.97870;,
 8307.62500;58.12560;-126.97870;,
 8306.68750;-1206.25879;-200.39005;,
 3749.32471;-1206.25879;-200.39005;,
 3754.81982;58.12560;148.39610;,
 8309.20117;58.12560;148.39610;,
 8308.68555;-1206.25879;148.39610;,
 3755.16162;-1206.25879;148.39610;,
 -539.27051;-1206.25879;-200.39005;,
 -538.78125;58.12560;-126.97870;,
 -534.54834;58.12560;152.55939;,
 -534.54834;-1206.25879;152.55939;,
 5198.41504;197.45656;-81.28730;,
 5450.02051;197.45656;-81.28730;,
 5450.02051;176.57056;-105.88700;,
 5198.41504;176.57056;-105.88700;,
 5450.02051;197.45656;120.62160;,
 5450.02051;176.57056;120.62160;,
 5198.41504;197.45656;120.62160;,
 5198.41504;176.57056;120.62160;,
 4156.06689;334.54590;-80.78640;,
 5094.85352;334.54590;-80.78640;,
 5094.85352;299.05670;-105.38610;,
 4156.06689;299.05670;-105.38610;,
 5094.85352;334.54590;125.93905;,
 5094.85352;299.05670;125.93905;,
 4156.06689;334.54590;125.93905;,
 4156.06689;299.05670;125.93905;,
 5544.39258;334.12024;-81.28730;,
 6483.16309;334.12024;-81.28730;,
 6483.16309;302.79141;-105.88700;,
 5544.39258;302.79141;-105.88700;,
 6483.16309;334.12024;120.62160;,
 6483.16309;302.79141;120.62160;,
 5544.39258;334.12024;120.62160;,
 5544.39258;302.79141;120.62160;,
 5198.41504;197.45656;-81.28730;,
 5450.02051;197.45656;-81.28730;,
 5450.02051;176.57056;-105.88700;,
 5198.41504;176.57056;-105.88700;,
 5450.02051;197.45656;120.62160;,
 5450.02051;176.57056;120.62160;,
 5198.41504;197.45656;120.62160;,
 5198.41504;176.57056;120.62160;;
 
 86;
 4;0,1,2,3;,
 4;0,3,4,5;,
 4;0,5,6,7;,
 4;0,7,8,1;,
 4;3,2,9,10;,
 4;3,10,11,4;,
 4;7,6,11,10;,
 4;7,10,9,8;,
 4;12,13,14,15;,
 4;12,15,2,1;,
 4;12,1,8,16;,
 4;12,16,17,13;,
 4;15,14,18,19;,
 4;15,19,9,2;,
 4;16,8,9,19;,
 4;16,19,18,17;,
 4;20,21,22,23;,
 4;20,23,14,13;,
 4;20,13,17,24;,
 4;20,24,25,21;,
 4;23,22,26,27;,
 4;23,27,18,14;,
 4;24,17,18,27;,
 4;24,27,26,25;,
 4;28,29,22,21;,
 4;28,21,25,30;,
 4;29,31,26,22;,
 4;30,25,26,31;,
 4;32,33,29,28;,
 4;34,32,28,30;,
 4;33,35,31,29;,
 4;35,34,30,31;,
 4;36,5,4,37;,
 4;36,37,38,39;,
 4;36,39,40,41;,
 4;36,41,6,5;,
 4;37,4,11,42;,
 4;37,42,43,38;,
 4;41,40,43,42;,
 4;41,42,11,6;,
 4;44,39,38,45;,
 4;44,46,40,39;,
 4;45,38,43,47;,
 4;46,47,43,40;,
 4;48,44,45,49;,
 4;48,50,46,44;,
 4;49,45,47,51;,
 4;50,51,47,46;,
 4;52,53,54,55;,
 4;52,55,33,32;,
 4;56,57,53,52;,
 4;56,52,32,34;,
 4;55,54,58,59;,
 4;55,59,35,33;,
 4;59,58,57,56;,
 4;59,56,34,35;,
 4;48,49,60,61;,
 4;50,48,61,62;,
 4;49,51,63,60;,
 4;51,50,62,63;,
 4;64,65,66,67;,
 4;65,68,69,66;,
 4;68,70,71,69;,
 4;70,64,67,71;,
 4;70,68,65,64;,
 4;67,66,69,71;,
 4;72,73,74,75;,
 4;73,76,77,74;,
 4;76,78,79,77;,
 4;78,72,75,79;,
 4;78,76,73,72;,
 4;75,74,77,79;,
 4;80,81,82,83;,
 4;81,84,85,82;,
 4;84,86,87,85;,
 4;86,80,83,87;,
 4;86,84,81,80;,
 4;83,82,85,87;,
 4;88,89,90,91;,
 4;89,92,93,90;,
 4;92,94,95,93;,
 4;94,88,91,95;,
 4;94,92,89,88;,
 4;91,90,93,95;,
 4;61,60,63,62;,
 4;58,54,53,57;;
 
 MeshMaterialList {
  4;
  86;
  0,
  0,
  1,
  1,
  0,
  0,
  2,
  2,
  0,
  0,
  1,
  1,
  0,
  0,
  2,
  2,
  0,
  0,
  1,
  1,
  0,
  0,
  2,
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
  1,
  0,
  0,
  2,
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
  1,
  0,
  0,
  2,
  2,
  0,
  1,
  0,
  2,
  0,
  0,
  2,
  0,
  1,
  0,
  0,
  0,
  2,
  0,
  1,
  0,
  0,
  0,
  2,
  0,
  1,
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
   0.480000;0.480000;0.480000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "\\data\\materialtexture\\OIP.jpg";
   }
  }
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "\\data\\materialtexture\\OIP.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "\\data\\materialtexture\\OIP.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  47;
  0.000373;0.057901;-0.998322;,
  0.013009;0.999915;-0.000431;,
  0.000000;-1.000000;-0.000000;,
  0.007881;0.056473;-0.998373;,
  0.269603;0.962962;-0.004306;,
  -0.007900;0.053554;-0.998534;,
  -0.269596;0.962954;0.006219;,
  -0.007900;0.056504;-0.998371;,
  0.007881;0.053523;-0.998536;,
  -0.008082;0.056307;-0.998381;,
  -0.277839;0.960626;0.001532;,
  -0.000416;0.057886;-0.998323;,
  -0.014470;0.999895;0.000128;,
  -0.007270;0.053441;-0.998545;,
  -0.249384;0.968404;0.001243;,
  0.009351;0.053560;-0.998521;,
  0.311068;0.950373;-0.005264;,
  0.000000;0.057963;-0.998319;,
  0.000000;1.000000;0.000000;,
  0.009189;0.053323;-0.998535;,
  0.309565;0.950788;-0.013142;,
  0.009152;0.056316;-0.998371;,
  0.307009;0.951619;-0.012920;,
  -0.005912;0.053361;-0.998558;,
  -0.208940;0.977909;0.006091;,
  -0.006323;0.056416;-0.998387;,
  -0.224262;0.974505;0.006739;,
  0.008956;0.056504;-0.998362;,
  0.296750;0.954942;-0.005119;,
  0.000000;0.057963;-0.998319;,
  0.000000;0.938697;-0.344745;,
  0.000000;0.762302;-0.647221;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.885913;-0.463852;,
  0.000000;0.569684;-0.821864;,
  0.000000;0.899326;-0.437278;,
  0.000000;0.617576;-0.786511;,
  0.002633;0.000000;0.999997;,
  0.005267;0.000000;0.999986;,
  0.004675;0.000000;0.999989;,
  0.002887;0.000000;0.999996;,
  0.001012;0.000000;1.000000;,
  0.000332;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  -0.999898;-0.000195;0.014259;,
  0.999984;-0.000408;-0.005726;;
  86;
  4;7,5,5,7;,
  4;7,7,0,0;,
  4;6,1,1,6;,
  4;6,6,6,6;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;33,38,38,33;,
  4;33,33,33,33;,
  4;8,3,3,8;,
  4;8,8,5,5;,
  4;4,6,6,4;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;33,33,33,33;,
  4;33,33,33,33;,
  4;11,9,9,11;,
  4;11,11,3,3;,
  4;12,4,4,12;,
  4;12,12,10,10;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;33,33,33,33;,
  4;33,33,33,33;,
  4;13,13,9,9;,
  4;14,10,10,14;,
  4;2,2,2,2;,
  4;33,33,33,33;,
  4;15,15,13,13;,
  4;16,16,14,14;,
  4;2,2,2,2;,
  4;33,33,33,33;,
  4;21,0,0,21;,
  4;21,21,19,19;,
  4;22,20,20,22;,
  4;22,22,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;39,40,40,39;,
  4;39,39,38,38;,
  4;23,19,19,23;,
  4;24,24,20,20;,
  4;2,2,2,2;,
  4;41,41,40,40;,
  4;25,23,23,25;,
  4;26,26,24,24;,
  4;2,2,2,2;,
  4;42,42,41,41;,
  4;27,17,17,27;,
  4;27,27,15,15;,
  4;28,18,18,28;,
  4;28,28,16,16;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;33,33,33,33;,
  4;33,33,33,33;,
  4;25,25,29,29;,
  4;26,26,18,18;,
  4;2,2,2,2;,
  4;42,42,43,43;,
  4;30,30,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;44,44,44,44;,
  4;18,18,30,30;,
  4;2,2,2,2;,
  4;34,34,35,35;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;44,44,44,44;,
  4;18,18,34,34;,
  4;2,2,2,2;,
  4;36,36,37,37;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;44,44,44,44;,
  4;18,18,36,36;,
  4;2,2,2,2;,
  4;30,30,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;44,44,44,44;,
  4;18,18,30,30;,
  4;2,2,2,2;,
  4;45,45,45,45;,
  4;46,46,46,46;;
 }
 MeshTextureCoords {
  96;
  97.628670;-0.081256;,
  99.999313;-1.518651;,
  99.968666;12.562588;,
  97.592911;12.562588;,
  95.217155;12.562588;,
  95.258018;-0.081256;,
  95.336220;-0.081256;,
  97.697090;-0.081256;,
  100.057968;-1.518651;,
  100.057968;12.562588;,
  97.697090;12.562588;,
  95.336220;12.562588;,
  102.369972;-1.518651;,
  104.740623;-0.081256;,
  104.720192;12.562588;,
  102.344429;12.562588;,
  102.418846;-1.518651;,
  104.779724;-0.081256;,
  104.779724;12.562588;,
  102.418846;12.562588;,
  107.111275;-0.081256;,
  109.481934;-0.149743;,
  109.471718;12.562588;,
  107.095955;12.562588;,
  107.140602;-0.081256;,
  109.501480;-0.149743;,
  109.501480;12.562588;,
  107.140602;12.562588;,
  111.852577;-1.549091;,
  111.847481;12.562588;,
  111.862358;-1.549091;,
  111.862358;12.562588;,
  114.110909;-1.480605;,
  114.081856;12.562588;,
  114.159843;-1.480605;,
  114.143837;12.562588;,
  93.191704;-0.134688;,
  93.144020;12.562588;,
  91.070900;12.562588;,
  91.125397;-1.534037;,
  91.256386;-1.534037;,
  93.296303;-0.134688;,
  93.296303;12.562588;,
  91.256386;12.562588;,
  88.524101;-1.616205;,
  88.484947;12.562588;,
  88.624557;-1.616205;,
  88.624557;12.562588;,
  85.382538;-0.081256;,
  85.362968;12.562588;,
  85.449783;-0.081256;,
  85.449783;12.562588;,
  116.146400;-0.081256;,
  150.322693;-0.081256;,
  150.313324;12.562588;,
  116.137527;12.562588;,
  116.192474;-0.081256;,
  150.338455;-0.081256;,
  150.333298;12.562588;,
  116.195892;12.562588;,
  82.003380;12.562588;,
  82.008270;-0.081256;,
  82.050598;-0.081256;,
  82.050598;12.562588;,
  129.782059;-1.474566;,
  132.298111;-1.474566;,
  132.298111;-1.265706;,
  129.782059;-1.265706;,
  132.298111;-1.474566;,
  132.298111;-1.265706;,
  129.782059;-1.474566;,
  129.782059;-1.265706;,
  119.358582;-2.845459;,
  128.746445;-2.845459;,
  128.746445;-2.490567;,
  119.358582;-2.490567;,
  128.746445;-2.845459;,
  128.746445;-2.490567;,
  119.358582;-2.845459;,
  119.358582;-2.490567;,
  133.241837;-2.841202;,
  142.629547;-2.841202;,
  142.629547;-2.527914;,
  133.241837;-2.527914;,
  142.629547;-2.841202;,
  142.629547;-2.527914;,
  133.241837;-2.841202;,
  133.241837;-2.527914;,
  129.782059;-1.474566;,
  132.298111;-1.474566;,
  132.298111;-1.265706;,
  129.782059;-1.265706;,
  132.298111;-1.474566;,
  132.298111;-1.265706;,
  129.782059;-1.474566;,
  129.782059;-1.265706;;
 }
}
