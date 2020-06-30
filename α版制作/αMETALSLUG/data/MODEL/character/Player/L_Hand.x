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
 4.14884;-0.69276;1.88367;,
 3.41316;0.35727;1.88367;,
 3.41316;0.35727;0.45983;,
 4.14884;-0.69276;0.45983;,
 2.09995;-0.08323;1.42761;,
 2.09995;-0.08323;0.45953;,
 1.47596;1.28619;2.44111;,
 2.09995;1.28619;2.39569;,
 2.09995;1.81370;2.39569;,
 1.47596;1.81370;2.44111;,
 1.47596;0.64620;2.44111;,
 2.09995;0.64519;2.39569;,
 4.14884;-0.69276;-0.96402;,
 3.41316;0.35727;-0.96402;,
 3.28007;0.58200;-1.08496;,
 3.55369;0.01155;-1.36106;,
 0.13461;1.28619;1.59774;,
 0.13461;0.64620;1.59774;,
 0.13461;1.81370;1.59774;,
 2.09995;-0.08323;-0.50856;,
 3.30229;0.42902;-1.64435;,
 3.14854;0.75627;-1.36533;,
 2.09995;0.64620;-1.47661;,
 4.65806;1.31512;-2.38783;,
 3.43556;0.28182;-1.63184;,
 4.90016;0.43381;-2.38783;,
 2.18470;2.24175;1.96549;,
 2.12477;2.13618;2.26969;,
 5.51530;2.49467;3.16930;,
 5.44999;2.61652;2.82839;,
 2.09995;1.88143;2.39569;,
 5.72923;2.25833;3.30748;,
 1.08623;1.88143;-1.51805;,
 1.12225;2.13618;-1.37152;,
 2.12272;2.13618;-1.34984;,
 2.09995;1.88143;-1.47661;,
 1.20928;2.24175;-1.01777;,
 2.17762;2.24175;-1.04372;,
 2.09995;-0.08323;-1.03591;,
 2.09995;0.38637;-1.34752;,
 3.16593;0.61909;-1.33928;,
 6.88664;-2.18515;-2.02031;,
 7.13322;-2.07397;-2.02008;,
 7.13307;-2.07497;2.91278;,
 6.88743;-2.18505;2.89346;,
 7.13322;-2.07397;-2.02008;,
 7.28294;-1.84876;-2.02031;,
 7.28172;-1.85255;2.91977;,
 7.13307;-2.07497;2.91278;,
 6.92369;-1.82720;-2.38783;,
 6.88252;-2.07696;-2.28142;,
 4.77543;-2.38384;-2.28198;,
 4.69987;-2.14348;-2.38783;,
 6.88252;-2.07696;-2.28142;,
 4.79667;-2.48684;-2.02537;,
 4.77543;-2.38384;-2.28198;,
 7.17692;-1.82713;-2.28142;,
 7.93510;0.56419;-2.28287;,
 8.03346;0.52314;-2.02170;,
 7.71904;0.69387;-2.38783;,
 4.35288;-2.22722;-2.02319;,
 4.53001;-2.43461;-2.02491;,
 4.52995;-2.43571;2.68619;,
 4.35429;-2.23087;2.67186;,
 4.79472;-2.48715;2.70655;,
 4.52336;-0.68902;3.03012;,
 4.25660;-0.69167;2.90706;,
 4.18736;-1.15598;2.91944;,
 4.36036;-1.34636;3.02704;,
 4.25660;-0.69167;2.90706;,
 4.14884;-0.69276;2.65128;,
 4.07044;-1.11053;2.64244;,
 4.18736;-1.15598;2.91944;,
 3.40769;0.17295;-1.49690;,
 4.27473;-0.64101;-2.26735;,
 4.14884;-0.69276;-1.97645;,
 4.57871;-0.51599;-2.38783;,
 5.95072;2.45134;-1.99644;,
 5.71354;2.57451;-1.97529;,
 5.70957;2.57560;2.88396;,
 5.94871;2.45277;2.90190;,
 5.45390;2.61652;-1.91539;,
 5.61756;2.26409;-2.35317;,
 5.85569;2.35384;-2.28920;,
 7.81993;0.92468;-2.28215;,
 7.87669;1.01450;-2.02461;,
 8.03331;0.79457;-2.02401;,
 8.03276;0.79497;2.94376;,
 8.03346;0.52314;2.94135;,
 7.87465;1.01602;2.94135;,
 5.89131;2.34636;3.20925;,
 7.81950;0.92490;3.20375;,
 7.71904;0.69387;3.30748;,
 7.93425;0.56264;3.20110;,
 7.54460;-0.65878;3.18161;,
 7.65983;-0.65762;2.91983;,
 7.27369;-0.66148;3.27336;,
 4.22361;-1.56503;2.91970;,
 4.45176;-2.19769;2.91818;,
 4.69883;-2.14172;3.03803;,
 4.11958;-1.63198;2.64241;,
 4.07060;-1.10965;-2.01620;,
 4.05821;-1.37164;-2.01998;,
 4.05729;-1.37481;-0.96402;,
 4.06910;-1.11781;-0.96402;,
 4.05821;-1.37164;-2.01998;,
 4.11994;-1.63284;-2.01620;,
 4.11689;-1.62509;-0.96402;,
 4.05729;-1.37481;-0.96402;,
 4.22996;-1.56641;-2.28625;,
 4.23893;-1.65369;-2.28003;,
 4.15421;-1.72037;-2.01971;,
 4.22996;-1.56641;-2.28625;,
 4.37461;-1.34489;-2.38783;,
 4.44337;-1.49261;-2.38783;,
 4.23893;-1.65369;-2.28003;,
 6.87864;-2.07312;3.15467;,
 4.77543;-2.38252;2.94314;,
 6.91560;-1.81429;3.26220;,
 5.72923;1.31512;3.30748;,
 6.88844;0.43381;3.30748;,
 0.13461;0.63907;1.59774;,
 0.13461;0.63907;0.45953;,
 0.13461;1.88143;1.59774;,
 0.13461;1.88143;-0.67868;,
 0.13461;0.63907;-0.67868;,
 0.49496;-0.08323;0.45953;,
 0.49496;-0.08323;1.25775;,
 1.08623;0.63907;-1.51805;,
 3.81602;1.02899;2.82230;,
 4.06910;-1.11781;1.88367;,
 4.06910;-1.11781;0.45983;,
 1.47596;1.88143;2.44111;,
 1.47596;0.63907;2.44111;,
 1.08623;1.88143;-1.51805;,
 1.08623;0.63907;-1.51805;,
 1.20928;-0.08323;-1.01777;,
 0.49496;-0.08323;-0.38768;,
 4.11689;-1.62509;1.88367;,
 4.11689;-1.62509;0.45983;,
 0.49496;2.24175;-0.38768;,
 0.49496;2.24175;1.25775;,
 1.58042;2.24175;1.94027;,
 3.41316;0.35727;2.48036;,
 2.09995;-0.08323;1.94348;,
 1.58042;-0.08323;1.94027;,
 1.50657;0.38433;2.29442;,
 0.24014;0.38433;1.49818;,
 1.50657;0.38433;2.29442;,
 0.24014;0.38433;1.49818;,
 2.09995;0.38578;2.26324;,
 2.09995;0.38578;2.26324;,
 1.50657;2.13618;2.29442;,
 0.24014;2.13618;-0.59345;,
 1.12225;2.13618;-1.37152;,
 0.24014;2.13618;-0.59345;,
 5.46949;2.48486;-2.22979;,
 1.12225;0.38433;-1.37152;,
 1.12225;0.38433;-1.37152;,
 0.24014;0.38433;-0.59345;,
 0.24014;0.38433;-0.59345;,
 3.54014;0.78844;2.77910;,
 3.54014;0.78844;2.77910;,
 4.19059;-1.15455;-2.28609;,
 7.17155;-1.82222;3.17631;,
 4.45320;-2.19561;-2.28132;,
 4.45320;-2.19561;-2.28132;,
 0.24014;0.38433;0.45953;,
 0.24014;0.38433;0.45953;,
 4.05729;-1.37481;0.45983;,
 4.05729;-1.37481;0.45983;,
 4.05729;-1.37481;1.88367;,
 4.05729;-1.37481;1.88367;,
 4.05842;-1.37540;2.63797;,
 4.05842;-1.37540;2.63797;,
 0.24014;2.13618;1.49818;,
 0.24014;2.13618;1.49818;,
 7.08982;-2.02282;-2.23366;,
 7.08982;-2.02282;-2.23366;,
 4.56306;-2.37834;-2.23465;,
 4.56306;-2.37834;-2.23465;,
 5.68290;2.49173;-2.22363;,
 7.97087;0.77505;-2.23502;,
 5.70130;2.49527;3.14659;,
 7.97020;0.77465;3.15569;,
 4.14015;-1.36910;2.87118;,
 4.14015;-1.36910;2.87118;,
 4.14958;-1.34996;-2.24478;,
 4.14958;-1.34996;-2.24478;,
 7.08595;-2.02065;3.12425;,
 4.56013;-2.37924;2.88042;;
 
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
  169;
  -0.241896;0.000000;0.970302;,
  -0.086636;0.000000;0.996240;,
  -0.086636;0.000000;0.996240;,
  -0.241896;0.000000;0.970302;,
  -0.089696;-0.109104;0.989975;,
  -0.149938;-0.088906;0.984690;,
  -0.091875;-0.096571;0.991077;,
  -0.117984;-0.006279;-0.992996;,
  -0.263761;-0.141490;-0.954155;,
  -0.102662;-0.232779;-0.967096;,
  -0.977433;-0.211246;0.000000;,
  -0.818989;-0.573810;0.000000;,
  0.161117;-0.986935;-0.000000;,
  -0.977434;-0.211239;-0.000004;,
  -0.818989;-0.573810;0.000000;,
  0.161117;-0.986935;-0.000000;,
  -0.875293;0.000000;0.483593;,
  -0.954288;-0.297068;0.032927;,
  -0.833661;-0.547022;0.076006;,
  0.160075;-0.977031;-0.140661;,
  -0.154299;-0.812810;0.561722;,
  -0.212284;-0.550120;0.807653;,
  -0.234736;-0.258568;0.937039;,
  0.054159;-0.881215;0.469604;,
  -0.079253;-0.450938;0.889030;,
  -0.236746;0.256501;0.937101;,
  -0.158164;0.784518;0.599596;,
  -0.032227;0.993072;0.113000;,
  -0.101228;0.218494;0.970574;,
  -0.111828;0.744569;0.658112;,
  -0.077126;0.983946;0.160940;,
  -0.041894;0.993136;-0.109209;,
  -0.212331;0.787303;-0.578852;,
  -0.325414;0.257879;-0.909728;,
  -0.129269;0.260970;-0.956653;,
  -0.117502;0.744990;-0.656645;,
  -0.062101;0.989412;-0.131180;,
  -0.205697;-0.813650;-0.543749;,
  -0.289015;-0.547882;-0.785045;,
  -0.324565;-0.258020;-0.909991;,
  0.116703;-0.536214;-0.835976;,
  0.162438;-0.833196;-0.528582;,
  0.636769;-0.751079;-0.174370;,
  0.266635;-0.946513;-0.181709;,
  0.238075;-0.699295;-0.674023;,
  0.198422;-0.233659;-0.951857;,
  0.651745;-0.348555;-0.673600;,
  0.890516;-0.417219;-0.181408;,
  -0.055816;-0.729608;-0.681584;,
  -0.015552;-0.983382;-0.180878;,
  -0.496597;-0.850355;-0.174032;,
  -0.848337;-0.498414;-0.178625;,
  -0.609149;-0.408084;-0.680004;,
  -0.096342;-0.165221;-0.981540;,
  -0.416069;-0.891236;-0.180512;,
  -0.788513;-0.509446;-0.344546;,
  -0.887266;-0.237130;-0.395637;,
  -0.819629;-0.504665;0.271146;,
  -0.384033;-0.302863;0.872234;,
  -0.200279;-0.093147;0.975301;,
  -0.952187;-0.173544;0.251441;,
  -0.651591;-0.047584;0.757077;,
  -0.172864;0.027796;0.984553;,
  -0.818594;-0.571912;0.053104;,
  -0.820300;-0.522933;0.231622;,
  0.219759;-0.542486;-0.810812;,
  -0.132079;-0.404650;-0.904883;,
  -0.605420;-0.317736;-0.729733;,
  -0.619422;-0.126191;-0.774850;,
  -0.873531;-0.450749;-0.183764;,
  -0.957497;-0.235089;-0.167128;,
  -0.771105;-0.106907;-0.627669;,
  -0.399240;0.041270;-0.915917;,
  -0.110160;0.741549;-0.661792;,
  -0.032515;0.983794;-0.176329;,
  0.279242;0.941751;-0.187428;,
  0.521530;0.830024;-0.197656;,
  0.329789;0.631263;-0.701959;,
  -0.053593;0.230554;-0.971582;,
  0.538388;0.480076;-0.692578;,
  0.694826;0.694630;-0.186294;,
  0.937921;0.300430;-0.173336;,
  0.970656;-0.208515;-0.119786;,
  0.731464;-0.077659;-0.677444;,
  0.180889;0.057285;-0.981834;,
  0.292418;0.942385;0.162486;,
  -0.022620;0.986495;0.162222;,
  -0.071393;0.768337;0.636051;,
  -0.109061;0.169902;0.979407;,
  0.380237;0.667138;0.640583;,
  0.526900;0.831513;0.175961;,
  0.937858;0.300783;0.173068;,
  0.695762;0.696059;0.177251;,
  0.556369;0.496745;0.666106;,
  0.228558;0.070376;0.970983;,
  0.723899;-0.085132;0.684633;,
  0.970142;-0.160621;0.181731;,
  -0.977819;-0.091905;0.188213;,
  -0.935720;-0.295369;0.192834;,
  -0.728913;-0.203870;0.653547;,
  -0.371426;-0.028555;0.928023;,
  -0.751350;0.072421;0.655918;,
  -0.973943;0.116904;0.194342;,
  0.933648;-0.298095;0.198596;,
  0.657435;-0.218504;0.721134;,
  0.055004;-0.043670;0.997531;,
  -0.974528;-0.087931;-0.206307;,
  -0.971111;0.125612;-0.202891;,
  -0.731433;0.081715;-0.677000;,
  -0.339150;-0.023770;-0.940432;,
  -0.717374;-0.172160;-0.675082;,
  -0.942783;-0.313038;-0.114746;,
  -0.913382;-0.315302;-0.257522;,
  -0.677951;-0.228799;-0.698594;,
  -0.192552;-0.072586;-0.978599;,
  0.615799;-0.345199;0.708258;,
  0.072527;-0.176345;0.981653;,
  0.174712;-0.694199;0.698258;,
  0.249836;-0.948947;0.192564;,
  0.628097;-0.755365;0.186862;,
  0.905035;-0.396372;0.154276;,
  -0.504035;-0.843927;0.183672;,
  -0.031034;-0.980658;0.193252;,
  -0.110673;-0.712437;0.692954;,
  -0.180557;-0.194152;0.964212;,
  -0.628460;-0.391491;0.672140;,
  -0.884094;-0.450547;0.124034;,
  0.000000;-1.000000;-0.000000;,
  -0.902234;-0.431246;0.000000;,
  -0.995277;-0.097076;0.000000;,
  -0.384620;-0.900844;0.201363;,
  -0.747126;-0.534637;0.394924;,
  -0.850330;-0.251873;0.462059;,
  -0.993295;0.115607;-0.000220;,
  -0.995627;-0.093417;-0.000563;,
  -0.960869;-0.277004;-0.000446;,
  -0.993316;0.115429;0.000000;,
  -0.995592;-0.093791;0.000000;,
  -0.953970;-0.299902;0.000000;,
  -0.993323;0.115363;0.000354;,
  -0.995583;-0.093887;0.000691;,
  -0.949851;-0.312701;0.000258;,
  -0.199884;0.976614;-0.079185;,
  -0.590678;0.766355;-0.252586;,
  -0.930000;0.188954;-0.315271;,
  -0.137838;0.988378;0.064113;,
  -0.551795;0.784222;0.283756;,
  -0.908115;0.200400;0.367649;,
  0.541003;-0.637383;-0.548688;,
  -0.419317;-0.715847;-0.558333;,
  0.175662;0.802074;-0.570806;,
  0.793029;0.254024;-0.553694;,
  0.231768;0.828677;0.509487;,
  0.793770;0.251375;0.553842;,
  -0.838200;-0.077215;0.539869;,
  -0.816357;-0.072613;-0.572965;,
  0.503332;-0.639748;0.580844;,
  -0.443906;-0.694318;0.566454;,
  0.318023;-0.948083;-0.000000;,
  0.318023;-0.948083;-0.000000;,
  0.319031;-0.905334;-0.280339;,
  0.301268;-0.760854;-0.574751;,
  0.254436;-0.065142;-0.964893;,
  0.318023;-0.948083;-0.000000;,
  -0.887775;-0.449562;-0.098740;,
  -0.148256;-0.545178;0.825107;,
  -0.878059;-0.478553;0.000000;,
  -0.742257;-0.665007;0.082590;,
  -0.934911;-0.176969;-0.307608;;
  180;
  4;13,14,11,10;,
  4;158,15,12,159;,
  4;0,1,2,3;,
  4;0,4,1,0;,
  4;17,18,64,63;,
  4;16,16,0,0;,
  4;16,16,0,3;,
  4;10,11,18,17;,
  4;159,12,19,160;,
  4;67,66,9,8;,
  4;68,67,8,7;,
  4;30,29,87,86;,
  4;29,28,88,87;,
  4;33,32,35,34;,
  4;32,31,36,35;,
  4;41,40,65,161;,
  4;40,9,66,65;,
  4;43,42,119,118;,
  4;42,47,120,119;,
  4;45,44,48,53;,
  4;44,43,49,48;,
  4;47,46,83,82;,
  4;46,45,84,83;,
  4;51,50,121,126;,
  4;50,49,122,121;,
  4;62,61,101,100;,
  4;61,60,102,101;,
  4;63,69,71,70;,
  4;69,68,72,71;,
  4;76,75,85,90;,
  4;75,74,86,85;,
  4;78,77,79,84;,
  4;77,76,80,79;,
  4;82,81,91,96;,
  4;81,80,92,91;,
  4;90,89,93,92;,
  4;89,88,94,93;,
  4;96,95,104,103;,
  4;95,94,105,104;,
  4;100,99,125,124;,
  4;99,98,126,125;,
  4;107,106,134,133;,
  4;106,111,135,134;,
  4;111,110,113,112;,
  4;110,109,114,113;,
  4;118,117,123,122;,
  4;117,116,124,123;,
  4;88,5,6,94;,
  3;84,7,78;,
  3;132,16,129;,
  3;16,16,129;,
  3;16,16,129;,
  3;16,147,129;,
  3;147,144,129;,
  3;144,56,129;,
  4;8,9,34,78;,
  3;5,88,4;,
  3;88,28,2;,
  3;88,2,1;,
  3;1,4,88;,
  4;127,12,15,130;,
  4;33,34,9,39;,
  3;94,6,105;,
  3;6,59,105;,
  3;59,62,105;,
  3;53,84,45;,
  4;139,13,10,136;,
  4;3,2,28,25;,
  3;22,4,0;,
  3;162,162,162;,
  4;72,7,114,109;,
  4;56,144,33,39;,
  4;37,41,19,54;,
  4;160,19,41,161;,
  4;133,17,70,107;,
  3;98,141,126;,
  3;126,141,111;,
  3;141,138,111;,
  3;138,135,111;,
  4;49,43,118,122;,
  3;142,145,31;,
  3;145,27,31;,
  3;31,27,36;,
  3;27,30,36;,
  4;36,30,86,74;,
  4;76,90,92,80;,
  3;47,82,120;,
  3;82,96,103;,
  3;103,120,82;,
  4;60,13,139,102;,
  4;57,14,13,60;,
  4;23,15,158,163;,
  4;130,15,23,20;,
  4;16,132,22,0;,
  4;147,16,3,25;,
  4;136,10,17,133;,
  4;54,19,12,127;,
  3;72,68,7;,
  3;17,63,70;,
  3;6,5,59;,
  3;105,62,116;,
  3;116,62,124;,
  3;62,100,124;,
  3;53,114,7;,
  3;53,7,84;,
  3;78,7,8;,
  4;126,111,112,51;,
  3;69,64,164;,
  4;20,21,131,130;,
  4;21,22,132,131;,
  4;22,21,24,4;,
  4;21,20,23,24;,
  4;27,26,29,30;,
  4;26,25,28,29;,
  4;31,32,143,142;,
  4;32,33,144,143;,
  4;34,35,73,78;,
  4;35,36,74,73;,
  4;37,38,40,41;,
  4;38,39,9,40;,
  4;39,38,55,56;,
  4;38,37,54,55;,
  4;4,24,58,59;,
  4;24,23,165,58;,
  4;59,58,61,62;,
  4;58,57,60,61;,
  4;70,71,108,107;,
  4;71,72,109,108;,
  4;103,104,115,120;,
  4;104,105,116,115;,
  4;53,52,113,114;,
  4;52,51,112,113;,
  4;56,55,128,129;,
  4;55,54,166,128;,
  4;129,128,131,132;,
  4;128,166,130,131;,
  4;133,134,137,136;,
  4;134,135,138,137;,
  4;136,137,140,139;,
  4;137,138,141,140;,
  4;98,97,140,141;,
  4;97,102,139,140;,
  4;142,143,146,145;,
  4;143,144,147,146;,
  4;25,26,146,147;,
  4;26,27,145,146;,
  4;46,47,42,148;,
  4;42,43,44,148;,
  4;44,45,46,148;,
  4;52,53,48,149;,
  4;48,49,50,149;,
  4;50,51,52,149;,
  4;77,78,73,150;,
  4;73,74,75,150;,
  4;75,76,77,150;,
  4;83,84,79,151;,
  4;79,80,81,151;,
  4;81,82,83,151;,
  4;89,90,85,152;,
  4;85,86,87,152;,
  4;87,88,89,152;,
  4;95,96,91,153;,
  4;91,92,93,153;,
  4;93,94,95,153;,
  4;101,102,97,154;,
  4;97,98,99,154;,
  4;99,100,101,154;,
  4;110,111,106,155;,
  4;106,107,108,155;,
  4;108,109,110,155;,
  4;119,120,115,156;,
  4;115,116,117,156;,
  4;117,118,119,156;,
  4;125,126,121,157;,
  4;121,122,123,157;,
  4;123,124,125,157;,
  3;167,164,167;,
  3;67,164,168;,
  3;63,64,69;,
  3;69,164,68;;
 }
 MeshTextureCoords {
  191;
  0.562500;0.937500;,
  0.499999;0.937501;,
  0.500000;0.875000;,
  0.562500;0.875000;,
  0.437500;0.937500;,
  0.437500;0.875000;,
  0.375000;0.113675;,
  0.437500;0.113676;,
  0.437500;0.185882;,
  0.375000;0.185882;,
  0.375000;0.055043;,
  0.437500;0.054892;,
  0.562500;0.812500;,
  0.499999;0.812500;,
  0.500000;0.798350;,
  0.516051;0.766051;,
  0.312500;0.113676;,
  0.312500;0.055043;,
  0.312500;0.185882;,
  0.437500;0.812500;,
  0.500000;0.740961;,
  0.478049;0.730668;,
  0.437500;0.694960;,
  0.500000;0.694957;,
  0.509385;0.741735;,
  0.562500;0.694957;,
  0.438796;0.275693;,
  0.437500;0.250000;,
  0.498347;0.246883;,
  0.495729;0.267227;,
  0.437500;0.196024;,
  0.500000;0.196340;,
  0.375000;0.553977;,
  0.375000;0.500000;,
  0.437500;0.500000;,
  0.437500;0.553977;,
  0.386723;0.466521;,
  0.438688;0.470145;,
  0.437500;0.778453;,
  0.437500;0.750000;,
  0.500193;0.758357;,
  0.857936;0.242834;,
  0.862418;0.250000;,
  0.637825;0.250000;,
  0.641655;0.242852;,
  0.625000;0.487418;,
  0.618838;0.483866;,
  0.618918;0.267020;,
  0.625000;0.262825;,
  0.617217;0.509050;,
  0.625000;0.508322;,
  0.625000;0.560457;,
  0.618367;0.590085;,
  0.875000;0.241678;,
  0.858171;0.193520;,
  0.875000;0.189543;,
  0.617622;0.500248;,
  0.566270;0.534837;,
  0.568880;0.483928;,
  0.562571;0.563875;,
  0.858071;0.136588;,
  0.858860;0.182799;,
  0.640006;0.182912;,
  0.642843;0.137174;,
  0.639363;0.193474;,
  0.565833;0.026667;,
  0.562500;0.000000;,
  0.605305;-0.000000;,
  0.622772;0.024187;,
  0.562500;1.000000;,
  0.562500;0.980592;,
  0.600587;0.980096;,
  0.605305;1.000000;,
  0.512244;0.755715;,
  0.562500;0.750000;,
  0.562500;0.768058;,
  0.562500;0.741362;,
  0.505766;0.482819;,
  0.498463;0.479499;,
  0.498372;0.265685;,
  0.505716;0.267804;,
  0.495788;0.475511;,
  0.498291;0.552797;,
  0.499652;0.528555;,
  0.555643;0.529308;,
  0.555922;0.484056;,
  0.561832;0.486516;,
  0.561813;0.263494;,
  0.568880;0.266072;,
  0.555869;0.266072;,
  0.500840;0.220158;,
  0.555711;0.219925;,
  0.562559;0.185685;,
  0.566208;0.215480;,
  0.593750;0.250000;,
  0.593750;0.267017;,
  0.590313;0.222505;,
  0.629962;0.046481;,
  0.631384;0.142896;,
  0.625000;0.139651;,
  0.644906;0.040815;,
  0.600504;0.766313;,
  0.625000;0.761526;,
  0.625000;0.812500;,
  0.601249;0.812500;,
  0.863474;-0.000000;,
  0.857746;0.040955;,
  0.809588;0.039708;,
  0.812500;0.000000;,
  0.875000;0.039249;,
  0.875000;0.055043;,
  0.857909;0.055043;,
  0.625000;0.710752;,
  0.618584;0.719775;,
  0.618391;0.694951;,
  0.625000;0.694957;,
  0.628968;0.234587;,
  0.629406;0.188483;,
  0.619929;0.221724;,
  0.500000;0.055043;,
  0.562500;0.055043;,
  0.312500;0.053977;,
  0.250000;0.053977;,
  0.312500;0.196024;,
  0.187500;0.196024;,
  0.187500;0.053977;,
  0.383960;0.875000;,
  0.383960;0.918831;,
  0.375000;0.696023;,
  0.480154;0.022931;,
  0.601249;0.937500;,
  0.601249;0.875000;,
  0.375000;0.196024;,
  0.375000;0.053977;,
  0.125000;0.196024;,
  0.125000;0.053977;,
  0.392163;0.787251;,
  0.383960;0.828479;,
  0.684588;0.039708;,
  0.747088;0.039708;,
  0.375000;0.427735;,
  0.382089;0.330261;,
  0.382089;0.279681;,
  0.500000;0.970998;,
  0.437500;0.970805;,
  0.397406;0.962884;,
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
  0.497652;0.503568;,
  0.375000;0.750000;,
  0.125000;0.000000;,
  0.187500;0.000000;,
  0.375000;0.812500;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.603762;0.737441;,
  0.619508;0.236561;,
  0.625000;0.597203;,
  0.875000;0.152797;,
  0.250000;0.000000;,
  0.375000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.000000;,
  0.625000;0.937500;,
  0.687500;0.000000;,
  0.639891;-0.000000;,
  0.625000;0.985109;,
  0.375000;0.312500;,
  0.312500;0.250000;,
  0.625000;0.500000;,
  0.875000;0.250000;,
  0.625000;0.564119;,
  0.875000;0.185881;,
  0.500000;0.500000;,
  0.562500;0.500000;,
  0.500000;0.250000;,
  0.562500;0.250000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.875000;0.000000;,
  0.625000;0.750000;,
  0.625000;0.250000;,
  0.625000;0.185881;;
 }
}
