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
 191;
 4.14885;-1.96313;1.88365;,
 3.41315;-0.91313;1.88365;,
 3.41315;-0.91313;0.45985;,
 4.14885;-1.96313;0.45985;,
 2.09995;-1.35363;1.42760;,
 2.09995;-1.35363;0.45955;,
 1.47595;0.01582;2.44110;,
 2.09995;0.01582;2.39570;,
 2.09995;0.54332;2.39570;,
 1.47595;0.54332;2.44110;,
 1.47595;-0.62418;2.44110;,
 2.09995;-0.62518;2.39570;,
 4.14885;-1.96313;-0.96400;,
 3.41315;-0.91313;-0.96400;,
 3.28005;-0.68838;-1.08495;,
 3.55370;-1.25883;-1.36105;,
 0.13460;0.01582;1.59775;,
 0.13460;-0.62418;1.59775;,
 0.13460;0.54332;1.59775;,
 2.09995;-1.35363;-0.50855;,
 3.30230;-0.84138;-1.64435;,
 3.14855;-0.51413;-1.36535;,
 2.09995;-0.62418;-1.47660;,
 4.65805;0.04472;-2.38785;,
 3.43555;-0.98858;-1.63185;,
 4.90015;-0.83658;-2.38785;,
 2.18470;0.97137;1.96550;,
 2.12475;0.86582;2.26970;,
 5.51530;1.22427;3.16930;,
 5.45000;1.34612;2.82840;,
 2.09995;0.61107;2.39570;,
 5.72925;0.98797;3.30750;,
 1.08625;0.61107;-1.51805;,
 1.12225;0.86582;-1.37150;,
 2.12270;0.86582;-1.34985;,
 2.09995;0.61107;-1.47660;,
 1.20930;0.97137;-1.01775;,
 2.17760;0.97137;-1.04370;,
 2.09995;-1.35363;-1.03590;,
 2.09995;-0.88403;-1.34750;,
 3.16595;-0.65128;-1.33930;,
 6.88665;-3.45553;-2.02030;,
 7.13320;-3.34433;-2.02010;,
 7.13305;-3.34533;2.91280;,
 6.88745;-3.45543;2.89345;,
 7.13320;-3.34433;-2.02010;,
 7.28295;-3.11913;-2.02030;,
 7.28170;-3.12293;2.91975;,
 7.13305;-3.34533;2.91280;,
 6.92370;-3.09758;-2.38785;,
 6.88250;-3.34733;-2.28140;,
 4.77545;-3.65423;-2.28200;,
 4.69985;-3.41388;-2.38785;,
 6.88250;-3.34733;-2.28140;,
 4.79665;-3.75723;-2.02535;,
 4.77545;-3.65423;-2.28200;,
 7.17690;-3.09753;-2.28140;,
 7.93510;-0.70618;-2.28285;,
 8.03345;-0.74723;-2.02170;,
 7.71905;-0.57653;-2.38785;,
 4.35290;-3.49758;-2.02320;,
 4.53000;-3.70498;-2.02490;,
 4.52995;-3.70608;2.68620;,
 4.35430;-3.50123;2.67185;,
 4.79470;-3.75753;2.70655;,
 4.52335;-1.95938;3.03010;,
 4.25660;-1.96203;2.90705;,
 4.18735;-2.42638;2.91945;,
 4.36035;-2.61673;3.02705;,
 4.25660;-1.96203;2.90705;,
 4.14885;-1.96313;2.65130;,
 4.07045;-2.38093;2.64245;,
 4.18735;-2.42638;2.91945;,
 3.40770;-1.09743;-1.49690;,
 4.27475;-1.91138;-2.26735;,
 4.14885;-1.96313;-1.97645;,
 4.57870;-1.78638;-2.38785;,
 5.95070;1.18097;-1.99645;,
 5.71355;1.30412;-1.97530;,
 5.70955;1.30522;2.88395;,
 5.94870;1.18237;2.90190;,
 5.45390;1.34612;-1.91540;,
 5.61755;0.99372;-2.35315;,
 5.85570;1.08347;-2.28920;,
 7.81995;-0.34568;-2.28215;,
 7.87670;-0.25588;-2.02460;,
 8.03330;-0.47583;-2.02400;,
 8.03275;-0.47543;2.94375;,
 8.03345;-0.74723;2.94135;,
 7.87465;-0.25438;2.94135;,
 5.89130;1.07597;3.20925;,
 7.81950;-0.34548;3.20375;,
 7.71905;-0.57653;3.30750;,
 7.93425;-0.70773;3.20110;,
 7.54460;-1.92918;3.18160;,
 7.65985;-1.92798;2.91985;,
 7.27370;-1.93188;3.27335;,
 4.22360;-2.83543;2.91970;,
 4.45175;-3.46808;2.91820;,
 4.69885;-3.41208;3.03805;,
 4.11960;-2.90238;2.64240;,
 4.07060;-2.38003;-2.01620;,
 4.05820;-2.64203;-2.02000;,
 4.05730;-2.64518;-0.96400;,
 4.06910;-2.38818;-0.96400;,
 4.05820;-2.64203;-2.02000;,
 4.11995;-2.90323;-2.01620;,
 4.11690;-2.89548;-0.96400;,
 4.05730;-2.64518;-0.96400;,
 4.22995;-2.83678;-2.28625;,
 4.23895;-2.92408;-2.28005;,
 4.15420;-2.99073;-2.01970;,
 4.22995;-2.83678;-2.28625;,
 4.37460;-2.61528;-2.38785;,
 4.44335;-2.76298;-2.38785;,
 4.23895;-2.92408;-2.28005;,
 6.87865;-3.34348;3.15465;,
 4.77545;-3.65288;2.94315;,
 6.91560;-3.08468;3.26220;,
 5.72925;0.04472;3.30750;,
 6.88845;-0.83658;3.30750;,
 0.13460;-0.63133;1.59775;,
 0.13460;-0.63133;0.45955;,
 0.13460;0.61107;1.59775;,
 0.13460;0.61107;-0.67870;,
 0.13460;-0.63133;-0.67870;,
 0.49495;-1.35363;0.45955;,
 0.49495;-1.35363;1.25775;,
 1.08625;-0.63133;-1.51805;,
 3.81600;-0.24138;2.82230;,
 4.06910;-2.38818;1.88365;,
 4.06910;-2.38818;0.45985;,
 1.47595;0.61107;2.44110;,
 1.47595;-0.63133;2.44110;,
 1.08625;0.61107;-1.51805;,
 1.08625;-0.63133;-1.51805;,
 1.20930;-1.35363;-1.01775;,
 0.49495;-1.35363;-0.38770;,
 4.11690;-2.89548;1.88365;,
 4.11690;-2.89548;0.45985;,
 0.49495;0.97137;-0.38770;,
 0.49495;0.97137;1.25775;,
 1.58040;0.97137;1.94025;,
 3.41315;-0.91313;2.48035;,
 2.09995;-1.35363;1.94350;,
 1.58040;-1.35363;1.94025;,
 1.50655;-0.88603;2.29440;,
 0.24015;-0.88603;1.49820;,
 1.50655;-0.88603;2.29440;,
 0.24015;-0.88603;1.49820;,
 2.09995;-0.88458;2.26325;,
 2.09995;-0.88458;2.26325;,
 1.50655;0.86582;2.29440;,
 0.24015;0.86582;-0.59345;,
 1.12225;0.86582;-1.37150;,
 0.24015;0.86582;-0.59345;,
 5.46950;1.21447;-2.22980;,
 1.12225;-0.88603;-1.37150;,
 1.12225;-0.88603;-1.37150;,
 0.24015;-0.88603;-0.59345;,
 0.24015;-0.88603;-0.59345;,
 3.54015;-0.48193;2.77910;,
 3.54015;-0.48193;2.77910;,
 4.19060;-2.42493;-2.28610;,
 7.17155;-3.09258;3.17630;,
 4.45320;-3.46598;-2.28130;,
 4.45320;-3.46598;-2.28130;,
 0.24015;-0.88603;0.45955;,
 0.24015;-0.88603;0.45955;,
 4.05730;-2.64518;0.45985;,
 4.05730;-2.64518;0.45985;,
 4.05730;-2.64518;1.88365;,
 4.05730;-2.64518;1.88365;,
 4.05840;-2.64578;2.63795;,
 4.05840;-2.64578;2.63795;,
 0.24015;0.86582;1.49820;,
 0.24015;0.86582;1.49820;,
 7.08980;-3.29318;-2.23365;,
 7.08980;-3.29318;-2.23365;,
 4.56305;-3.64873;-2.23465;,
 4.56305;-3.64873;-2.23465;,
 5.68290;1.22137;-2.22365;,
 7.97085;-0.49533;-2.23500;,
 5.70130;1.22487;3.14660;,
 7.97020;-0.49573;3.15570;,
 4.14015;-2.63948;2.87120;,
 4.14015;-2.63948;2.87120;,
 4.14960;-2.62033;-2.24480;,
 4.14960;-2.62033;-2.24480;,
 7.08595;-3.29103;3.12425;,
 4.56015;-3.64963;2.88040;;
 
 180;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;10,11,7,6;,
 4;12,13,14,15;,
 4;16,17,10,6;,
 4;18,16,6,9;,
 4;3,2,13,12;,
 4;2,5,19,13;,
 4;20,21,22,23;,
 4;24,20,23,25;,
 4;26,27,28,29;,
 4;27,30,31,28;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;38,39,40,14;,
 4;39,22,21,40;,
 4;41,42,43,44;,
 4;45,46,47,48;,
 4;49,50,51,52;,
 4;53,41,54,55;,
 4;46,56,57,58;,
 4;56,49,59,57;,
 4;60,61,62,63;,
 4;61,54,64,62;,
 4;65,66,67,68;,
 4;69,70,71,72;,
 4;15,73,74,75;,
 4;73,24,76,74;,
 4;77,78,79,80;,
 4;78,81,29,79;,
 4;82,83,84,59;,
 4;83,77,85,84;,
 4;58,86,87,88;,
 4;86,85,89,87;,
 4;80,90,91,89;,
 4;90,31,92,91;,
 4;88,93,94,95;,
 4;93,92,96,94;,
 4;68,97,98,99;,
 4;97,100,63,98;,
 4;101,102,103,104;,
 4;105,106,107,108;,
 4;106,109,110,111;,
 4;112,113,114,115;,
 4;44,116,117,64;,
 4;116,118,99,117;,
 4;31,119,120,92;,
 3;59,25,82;,
 3;121,17,122;,
 3;17,16,122;,
 3;16,18,122;,
 3;18,123,122;,
 3;123,124,122;,
 3;124,125,122;,
 4;23,22,35,82;,
 3;119,31,11;,
 3;31,30,8;,
 3;31,8,7;,
 3;7,11,31;,
 4;126,5,4,127;,
 4;32,35,22,128;,
 3;92,120,96;,
 3;120,129,96;,
 3;129,65,96;,
 3;52,59,49;,
 4;130,0,3,131;,
 4;9,8,30,132;,
 3;133,11,10;,
 3;119,11,129;,
 4;76,25,114,113;,
 4;125,124,134,135;,
 4;136,38,19,137;,
 4;13,19,38,14;,
 4;104,12,75,101;,
 3;100,138,63;,
 3;63,138,106;,
 3;138,139,106;,
 3;139,107,106;,
 4;54,41,44,64;,
 3;140,141,36;,
 3;141,142,36;,
 3;36,142,37;,
 3;142,26,37;,
 4;37,26,29,81;,
 4;77,80,89,85;,
 3;46,58,47;,
 3;58,88,95;,
 3;95,47,58;,
 4;70,0,130,71;,
 4;143,1,0,70;,
 4;144,4,1,143;,
 4;127,4,144,145;,
 4;17,121,133,10;,
 4;123,18,9,132;,
 4;131,3,12,104;,
 4;137,19,5,126;,
 3;76,24,25;,
 3;12,15,75;,
 3;120,119,129;,
 3;96,65,118;,
 3;118,65,99;,
 3;65,68,99;,
 3;52,114,25;,
 3;52,25,59;,
 3;82,25,23;,
 4;63,106,111,60;,
 3;73,14,40;,
 4;145,146,147,127;,
 4;148,133,121,149;,
 4;133,148,150,11;,
 4;146,145,144,151;,
 4;142,152,27,26;,
 4;152,132,30,27;,
 4;36,33,153,140;,
 4;154,134,124,155;,
 4;35,34,156,82;,
 4;34,37,81,156;,
 4;136,157,39,38;,
 4;157,128,22,39;,
 4;135,158,159,125;,
 4;157,136,137,160;,
 4;11,150,161,129;,
 4;151,144,143,162;,
 4;129,161,66,65;,
 4;162,143,70,69;,
 4;75,74,163,101;,
 4;74,76,113,163;,
 4;95,94,164,47;,
 4;94,96,118,164;,
 4;52,165,115,114;,
 4;166,60,111,110;,
 4;125,159,167,122;,
 4;160,137,126,168;,
 4;122,167,149,121;,
 4;168,126,127,147;,
 4;104,103,169,131;,
 4;108,107,139,170;,
 4;131,169,171,130;,
 4;170,139,138,172;,
 4;100,173,172,138;,
 4;174,71,130,171;,
 4;140,153,175,141;,
 4;155,124,123,176;,
 4;132,152,176,123;,
 4;152,142,141,175;,
 4;56,46,45,177;,
 4;42,41,53,178;,
 4;50,49,56,177;,
 4;165,52,51,179;,
 4;55,54,61,180;,
 4;61,60,166,180;,
 4;83,82,156,181;,
 4;156,81,78,181;,
 4;78,77,83,181;,
 4;57,59,84,182;,
 4;84,85,86,182;,
 4;86,58,57,182;,
 4;90,80,79,183;,
 4;79,29,28,183;,
 4;28,31,90,183;,
 4;93,88,87,184;,
 4;87,89,91,184;,
 4;91,92,93,184;,
 4;72,71,174,185;,
 4;173,100,97,186;,
 4;97,68,67,186;,
 4;109,106,105,187;,
 4;102,101,163,188;,
 4;163,113,112,188;,
 4;48,47,164,189;,
 4;164,118,116,189;,
 4;116,44,43,189;,
 4;98,63,62,190;,
 4;62,64,117,190;,
 4;117,99,98,190;,
 3;24,40,20;,
 3;20,40,21;,
 3;15,14,73;,
 3;73,40,24;;
 
 MeshMaterialList {
  1;
  180;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  171;
  -0.241902;0.000000;0.970301;,
  -0.086646;0.000000;0.996239;,
  -0.086646;0.000000;0.996239;,
  -0.241902;0.000000;0.970301;,
  -0.241902;0.000000;0.970301;,
  -0.089705;-0.109120;0.989973;,
  -0.149941;-0.088909;0.984689;,
  -0.091877;-0.096586;0.991075;,
  -0.117984;-0.006269;-0.992996;,
  -0.263762;-0.141476;-0.954156;,
  -0.102667;-0.232800;-0.967090;,
  -0.977432;-0.211249;0.000000;,
  -0.818975;-0.573829;0.000000;,
  0.161117;-0.986935;-0.000000;,
  -0.977433;-0.211246;-0.000002;,
  -0.818975;-0.573829;0.000000;,
  0.161117;-0.986935;-0.000000;,
  -0.875291;0.000000;0.483596;,
  -0.875291;0.000000;0.483596;,
  -0.875291;0.000000;0.483596;,
  -0.954287;-0.297075;0.032918;,
  -0.833649;-0.547042;0.075986;,
  0.160077;-0.977031;-0.140662;,
  -0.154322;-0.812788;0.561747;,
  -0.212296;-0.550125;0.807646;,
  -0.234739;-0.258600;0.937029;,
  0.054143;-0.881204;0.469625;,
  -0.079269;-0.450938;0.889028;,
  -0.236753;0.256510;0.937097;,
  -0.158165;0.784535;0.599574;,
  -0.032225;0.993074;0.112985;,
  -0.101240;0.218507;0.970569;,
  -0.111834;0.744586;0.658091;,
  -0.077148;0.983946;0.160927;,
  -0.041890;0.993137;-0.109195;,
  -0.212318;0.787326;-0.578825;,
  -0.325402;0.257899;-0.909726;,
  -0.129268;0.260959;-0.956656;,
  -0.117502;0.744997;-0.656638;,
  -0.062116;0.989413;-0.131161;,
  -0.205708;-0.813626;-0.543780;,
  -0.289005;-0.547904;-0.785033;,
  -0.324547;-0.258076;-0.909981;,
  0.116694;-0.536233;-0.835965;,
  0.162437;-0.833191;-0.528590;,
  0.636768;-0.751075;-0.174390;,
  0.266677;-0.946499;-0.181724;,
  0.238105;-0.699318;-0.673989;,
  0.198488;-0.233725;-0.951827;,
  0.651766;-0.348605;-0.673554;,
  0.890498;-0.417251;-0.181424;,
  -0.055857;-0.729635;-0.681552;,
  -0.015584;-0.983385;-0.180864;,
  -0.496665;-0.850321;-0.174005;,
  -0.848358;-0.498384;-0.178613;,
  -0.609208;-0.408082;-0.679952;,
  -0.096376;-0.165248;-0.981532;,
  -0.416093;-0.891222;-0.180529;,
  -0.788496;-0.509473;-0.344545;,
  -0.887248;-0.237199;-0.395636;,
  -0.819618;-0.504676;0.271161;,
  -0.384025;-0.302864;0.872237;,
  -0.200281;-0.093169;0.975299;,
  -0.952184;-0.173549;0.251448;,
  -0.651585;-0.047576;0.757083;,
  -0.172853;0.027810;0.984555;,
  -0.818590;-0.571921;0.053075;,
  -0.820320;-0.522933;0.231550;,
  0.219749;-0.542504;-0.810802;,
  -0.132093;-0.404667;-0.904873;,
  -0.605434;-0.317749;-0.729716;,
  -0.619458;-0.126224;-0.774816;,
  -0.873526;-0.450758;-0.183764;,
  -0.957497;-0.235083;-0.167139;,
  -0.771123;-0.106919;-0.627644;,
  -0.399275;0.041253;-0.915903;,
  -0.110192;0.741529;-0.661810;,
  -0.032550;0.983799;-0.176297;,
  0.279241;0.941758;-0.187391;,
  0.521544;0.830023;-0.197621;,
  0.329787;0.631246;-0.701975;,
  -0.053603;0.230518;-0.971591;,
  0.538460;0.480042;-0.692547;,
  0.694864;0.694601;-0.186263;,
  0.937936;0.300391;-0.173325;,
  0.970656;-0.208511;-0.119794;,
  0.731513;-0.077675;-0.677388;,
  0.180938;0.057266;-0.981826;,
  0.292419;0.942383;0.162496;,
  -0.022648;0.986493;0.162229;,
  -0.071390;0.768359;0.636025;,
  -0.109051;0.169932;0.979403;,
  0.380260;0.667178;0.640528;,
  0.526908;0.831510;0.175952;,
  0.937869;0.300766;0.173034;,
  0.695775;0.696052;0.177225;,
  0.556401;0.496777;0.666056;,
  0.228592;0.070386;0.970974;,
  0.723924;-0.085134;0.684607;,
  0.970145;-0.160617;0.181718;,
  -0.977821;-0.091919;0.188196;,
  -0.935719;-0.295401;0.192791;,
  -0.728933;-0.203895;0.653516;,
  -0.371408;-0.028540;0.928031;,
  -0.751350;0.072430;0.655917;,
  -0.973942;0.116917;0.194336;,
  0.933648;-0.298099;0.198592;,
  0.657448;-0.218514;0.721120;,
  0.055014;-0.043686;0.997529;,
  -0.974525;-0.087933;-0.206324;,
  -0.971107;0.125620;-0.202904;,
  -0.731449;0.081725;-0.676981;,
  -0.339216;-0.023755;-0.940409;,
  -0.717395;-0.172165;-0.675058;,
  -0.942824;-0.312917;-0.114748;,
  -0.913374;-0.315326;-0.257521;,
  -0.677983;-0.228821;-0.698556;,
  -0.192605;-0.072593;-0.978588;,
  0.615814;-0.345205;0.708242;,
  0.072532;-0.176353;0.981651;,
  0.174707;-0.694196;0.698262;,
  0.249863;-0.948936;0.192585;,
  0.628117;-0.755353;0.186846;,
  0.905031;-0.396387;0.154260;,
  -0.504066;-0.843911;0.183661;,
  -0.031058;-0.980652;0.193279;,
  -0.110660;-0.712446;0.692947;,
  -0.180535;-0.194168;0.964212;,
  -0.628475;-0.391541;0.672097;,
  -0.884098;-0.450548;0.124003;,
  0.000000;-1.000000;-0.000000;,
  -0.902224;-0.431267;0.000000;,
  -0.995274;-0.097107;0.000000;,
  -0.384641;-0.900833;0.201374;,
  -0.747115;-0.534656;0.394921;,
  -0.850315;-0.251928;0.462057;,
  -0.993296;0.115602;-0.000219;,
  -0.995626;-0.093426;-0.000556;,
  -0.960914;-0.276847;-0.000439;,
  -0.993317;0.115417;0.000000;,
  -0.995591;-0.093801;0.000000;,
  -0.954046;-0.299661;0.000000;,
  -0.993323;0.115366;0.000354;,
  -0.995582;-0.093899;0.000685;,
  -0.949878;-0.312621;0.000258;,
  -0.199870;0.976618;-0.079179;,
  -0.590644;0.766385;-0.252574;,
  -0.929993;0.188984;-0.315274;,
  -0.137828;0.988380;0.064104;,
  -0.551769;0.784245;0.283744;,
  -0.908110;0.200420;0.367652;,
  0.540995;-0.637407;-0.548668;,
  -0.419411;-0.715832;-0.558282;,
  0.175638;0.802077;-0.570810;,
  0.793086;0.253970;-0.553637;,
  0.231764;0.828693;0.509463;,
  0.793801;0.251383;0.553793;,
  -0.838205;-0.077235;0.539858;,
  -0.816352;-0.072613;-0.572972;,
  0.503345;-0.639748;0.580832;,
  -0.443888;-0.694356;0.566421;,
  0.318025;-0.948082;-0.000000;,
  0.318025;-0.948082;-0.000000;,
  0.319034;-0.905333;-0.280340;,
  0.301273;-0.760854;-0.574749;,
  0.254441;-0.065167;-0.964890;,
  -0.887783;-0.449549;-0.098729;,
  -0.148263;-0.545142;0.825129;,
  -0.878097;-0.478484;0.000000;,
  -0.742309;-0.664948;0.082586;,
  -0.934915;-0.177029;-0.307564;;
  180;
  4;14,15,12,11;,
  4;161,16,13,162;,
  4;0,1,2,3;,
  4;4,5,1,0;,
  4;20,21,67,66;,
  4;18,17,4,0;,
  4;19,18,0,3;,
  4;11,12,21,20;,
  4;162,13,22,163;,
  4;70,69,10,9;,
  4;71,70,9,8;,
  4;33,32,90,89;,
  4;32,31,91,90;,
  4;36,35,38,37;,
  4;35,34,39,38;,
  4;44,43,68,164;,
  4;43,10,69,68;,
  4;46,45,122,121;,
  4;45,50,123,122;,
  4;48,47,51,56;,
  4;47,46,52,51;,
  4;50,49,86,85;,
  4;49,48,87,86;,
  4;54,53,124,129;,
  4;53,52,125,124;,
  4;65,64,104,103;,
  4;64,63,105,104;,
  4;66,72,74,73;,
  4;72,71,75,74;,
  4;79,78,88,93;,
  4;78,77,89,88;,
  4;81,80,82,87;,
  4;80,79,83,82;,
  4;85,84,94,99;,
  4;84,83,95,94;,
  4;93,92,96,95;,
  4;92,91,97,96;,
  4;99,98,107,106;,
  4;98,97,108,107;,
  4;103,102,128,127;,
  4;102,101,129,128;,
  4;110,109,137,136;,
  4;109,114,138,137;,
  4;114,113,116,115;,
  4;113,112,117,116;,
  4;121,120,126,125;,
  4;120,119,127,126;,
  4;91,6,7,97;,
  3;87,8,81;,
  3;135,17,132;,
  3;17,18,132;,
  3;18,19,132;,
  3;19,150,132;,
  3;150,147,132;,
  3;147,59,132;,
  4;9,10,37,81;,
  3;6,91,5;,
  3;91,31,2;,
  3;91,2,1;,
  3;1,5,91;,
  4;130,13,16,133;,
  4;36,37,10,42;,
  3;97,7,108;,
  3;7,62,108;,
  3;62,65,108;,
  3;56,87,48;,
  4;142,14,11,139;,
  4;3,2,31,28;,
  3;25,5,4;,
  3;165,165,165;,
  4;75,8,117,112;,
  4;59,147,36,42;,
  4;40,44,22,57;,
  4;163,22,44,164;,
  4;136,20,73,110;,
  3;101,144,129;,
  3;129,144,114;,
  3;144,141,114;,
  3;141,138,114;,
  4;52,46,121,125;,
  3;145,148,34;,
  3;148,30,34;,
  3;34,30,39;,
  3;30,33,39;,
  4;39,33,89,77;,
  4;79,93,95,83;,
  3;50,85,123;,
  3;85,99,106;,
  3;106,123,85;,
  4;63,14,142,105;,
  4;60,15,14,63;,
  4;26,16,161,161;,
  4;133,16,26,23;,
  4;17,135,25,4;,
  4;150,19,3,28;,
  4;139,11,20,136;,
  4;57,22,13,130;,
  3;75,71,8;,
  3;20,66,73;,
  3;7,6,62;,
  3;108,65,119;,
  3;119,65,127;,
  3;65,103,127;,
  3;56,117,8;,
  3;56,8,87;,
  3;81,8,9;,
  4;129,114,115,54;,
  3;72,67,166;,
  4;23,24,134,133;,
  4;24,25,135,134;,
  4;25,24,27,5;,
  4;24,23,26,27;,
  4;30,29,32,33;,
  4;29,28,31,32;,
  4;34,35,146,145;,
  4;35,36,147,146;,
  4;37,38,76,81;,
  4;38,39,77,76;,
  4;40,41,43,44;,
  4;41,42,10,43;,
  4;42,41,58,59;,
  4;41,40,57,58;,
  4;5,27,61,62;,
  4;27,26,167,61;,
  4;62,61,64,65;,
  4;61,60,63,64;,
  4;73,74,111,110;,
  4;74,75,112,111;,
  4;106,107,118,123;,
  4;107,108,119,118;,
  4;56,55,116,117;,
  4;55,54,115,116;,
  4;59,58,131,132;,
  4;58,57,168,131;,
  4;132,131,134,135;,
  4;131,168,133,134;,
  4;136,137,140,139;,
  4;137,138,141,140;,
  4;139,140,143,142;,
  4;140,141,144,143;,
  4;101,100,143,144;,
  4;100,105,142,143;,
  4;145,146,149,148;,
  4;146,147,150,149;,
  4;28,29,149,150;,
  4;29,30,148,149;,
  4;49,50,45,151;,
  4;45,46,47,151;,
  4;47,48,49,151;,
  4;55,56,51,152;,
  4;51,52,53,152;,
  4;53,54,55,152;,
  4;80,81,76,153;,
  4;76,77,78,153;,
  4;78,79,80,153;,
  4;86,87,82,154;,
  4;82,83,84,154;,
  4;84,85,86,154;,
  4;92,93,88,155;,
  4;88,89,90,155;,
  4;90,91,92,155;,
  4;98,99,94,156;,
  4;94,95,96,156;,
  4;96,97,98,156;,
  4;104,105,100,157;,
  4;100,101,102,157;,
  4;102,103,104,157;,
  4;113,114,109,158;,
  4;109,110,111,158;,
  4;111,112,113,158;,
  4;122,123,118,159;,
  4;118,119,120,159;,
  4;120,121,122,159;,
  4;128,129,124,160;,
  4;124,125,126,160;,
  4;126,127,128,160;,
  3;169,166,169;,
  3;70,166,170;,
  3;66,67,72;,
  3;72,166,71;;
 }
 MeshTextureCoords {
  191;
  0.562500;0.937500;,
  0.500000;0.937500;,
  0.500000;0.875000;,
  0.562500;0.875000;,
  0.437500;0.937500;,
  0.437500;0.875000;,
  0.375000;0.113670;,
  0.437500;0.113680;,
  0.437500;0.185880;,
  0.375000;0.185880;,
  0.375000;0.055040;,
  0.437500;0.054890;,
  0.562500;0.812500;,
  0.500000;0.812500;,
  0.500000;0.798350;,
  0.516050;0.766050;,
  0.312500;0.113680;,
  0.312500;0.055040;,
  0.312500;0.185880;,
  0.437500;0.812500;,
  0.500000;0.740960;,
  0.478050;0.730670;,
  0.437500;0.694960;,
  0.500000;0.694960;,
  0.509380;0.741730;,
  0.562500;0.694960;,
  0.438800;0.275690;,
  0.437500;0.250000;,
  0.498350;0.246880;,
  0.495730;0.267230;,
  0.437500;0.196020;,
  0.500000;0.196340;,
  0.375000;0.553980;,
  0.375000;0.500000;,
  0.437500;0.500000;,
  0.437500;0.553980;,
  0.386720;0.466520;,
  0.438690;0.470140;,
  0.437500;0.778450;,
  0.437500;0.750000;,
  0.500190;0.758360;,
  0.857940;0.242830;,
  0.862420;0.250000;,
  0.637830;0.250000;,
  0.641660;0.242850;,
  0.625000;0.487420;,
  0.618840;0.483870;,
  0.618920;0.267020;,
  0.625000;0.262830;,
  0.617220;0.509050;,
  0.625000;0.508320;,
  0.625000;0.560460;,
  0.618370;0.590090;,
  0.875000;0.241680;,
  0.858170;0.193520;,
  0.875000;0.189540;,
  0.617620;0.500250;,
  0.566270;0.534840;,
  0.568880;0.483930;,
  0.562570;0.563880;,
  0.858070;0.136590;,
  0.858860;0.182800;,
  0.640010;0.182910;,
  0.642840;0.137170;,
  0.639360;0.193470;,
  0.565830;0.026670;,
  0.562500;0.000000;,
  0.605310;-0.000000;,
  0.622770;0.024190;,
  0.562500;1.000000;,
  0.562500;0.980590;,
  0.600590;0.980100;,
  0.605310;1.000000;,
  0.512240;0.755720;,
  0.562500;0.750000;,
  0.562500;0.768060;,
  0.562500;0.741360;,
  0.505770;0.482820;,
  0.498460;0.479500;,
  0.498370;0.265680;,
  0.505720;0.267800;,
  0.495790;0.475510;,
  0.498290;0.552800;,
  0.499650;0.528550;,
  0.555640;0.529310;,
  0.555920;0.484060;,
  0.561830;0.486520;,
  0.561810;0.263490;,
  0.568880;0.266070;,
  0.555870;0.266070;,
  0.500840;0.220160;,
  0.555710;0.219930;,
  0.562560;0.185680;,
  0.566210;0.215480;,
  0.593750;0.250000;,
  0.593750;0.267020;,
  0.590310;0.222510;,
  0.629960;0.046480;,
  0.631380;0.142900;,
  0.625000;0.139650;,
  0.644910;0.040810;,
  0.600500;0.766310;,
  0.625000;0.761530;,
  0.625000;0.812500;,
  0.601250;0.812500;,
  0.863470;-0.000000;,
  0.857750;0.040950;,
  0.809590;0.039710;,
  0.812500;0.000000;,
  0.875000;0.039250;,
  0.875000;0.055040;,
  0.857910;0.055040;,
  0.625000;0.710750;,
  0.618580;0.719780;,
  0.618390;0.694950;,
  0.625000;0.694960;,
  0.628970;0.234590;,
  0.629410;0.188480;,
  0.619930;0.221720;,
  0.500000;0.055040;,
  0.562500;0.055040;,
  0.312500;0.053980;,
  0.250000;0.053980;,
  0.312500;0.196020;,
  0.187500;0.196020;,
  0.187500;0.053980;,
  0.383960;0.875000;,
  0.383960;0.918830;,
  0.375000;0.696020;,
  0.480150;0.022930;,
  0.601250;0.937500;,
  0.601250;0.875000;,
  0.375000;0.196020;,
  0.375000;0.053980;,
  0.125000;0.196020;,
  0.125000;0.053980;,
  0.392160;0.787250;,
  0.383960;0.828480;,
  0.684590;0.039710;,
  0.747090;0.039710;,
  0.375000;0.427740;,
  0.382090;0.330260;,
  0.382090;0.279680;,
  0.500000;0.971000;,
  0.437500;0.970800;,
  0.397410;0.962880;,
  0.375000;1.000000;,
  0.375000;0.937500;,
  0.375000;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.437500;1.000000;,
  0.375000;0.250000;,
  0.375000;0.437500;,
  0.125000;0.250000;,
  0.187500;0.250000;,
  0.497650;0.503570;,
  0.375000;0.750000;,
  0.125000;0.000000;,
  0.187500;0.000000;,
  0.375000;0.812500;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.603760;0.737440;,
  0.619510;0.236560;,
  0.625000;0.597200;,
  0.875000;0.152800;,
  0.250000;0.000000;,
  0.375000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.000000;,
  0.625000;0.937500;,
  0.687500;0.000000;,
  0.639890;-0.000000;,
  0.625000;0.985110;,
  0.375000;0.312500;,
  0.312500;0.250000;,
  0.625000;0.500000;,
  0.875000;0.250000;,
  0.625000;0.564120;,
  0.875000;0.185880;,
  0.500000;0.500000;,
  0.562500;0.500000;,
  0.500000;0.250000;,
  0.562500;0.250000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.875000;0.000000;,
  0.625000;0.750000;,
  0.625000;0.250000;,
  0.625000;0.185880;;
 }
}
