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
 200;
 -2.14298;-7.00195;-1.63138;,
 -1.96010;-7.03374;-1.60476;,
 -1.98456;-6.74441;-1.45038;,
 -2.05330;-6.53795;-1.41079;,
 -2.30685;-6.74347;-1.63373;,
 -1.83564;-7.04910;-1.60370;,
 -1.49569;-6.89931;-1.54493;,
 -1.68086;-6.68939;-1.36346;,
 -1.74907;-6.35413;-1.29366;,
 -1.45346;-6.53889;-1.52094;,
 -1.50860;-6.44985;-1.41713;,
 -1.52479;-6.23642;-1.44710;,
 -2.14503;-6.24850;-1.53995;,
 -2.38504;-6.57285;-1.62528;,
 -1.89729;-6.09173;-1.40194;,
 -1.69106;-6.11143;-1.34827;,
 -0.27790;-3.22921;-2.38700;,
 -0.17561;-3.59461;-2.30600;,
 -0.70137;-5.57318;-2.61146;,
 -0.90090;-5.58567;-2.91739;,
 -0.37057;-5.25030;-2.33967;,
 -0.65820;-5.57336;-2.36336;,
 -0.59415;-5.42062;-2.17368;,
 -0.69849;-5.54503;-2.11339;,
 -0.81973;-5.26602;-1.98646;,
 -1.21235;-5.13569;-1.82717;,
 -1.24402;-5.15552;-2.05028;,
 -1.60461;-5.09769;-1.86459;,
 -1.30449;-4.92959;-2.02418;,
 -1.78198;-5.13241;-1.94787;,
 -1.40777;-4.94396;-2.07790;,
 -1.93207;-5.18185;-2.16535;,
 -1.32754;-3.74523;-1.90951;,
 -2.00779;-5.30590;-2.54372;,
 -1.80596;-5.33441;-2.77680;,
 -1.22349;-3.41531;-2.04072;,
 -1.44965;-5.40878;-3.04936;,
 -0.91205;-3.11313;-2.07403;,
 -0.56799;-2.97354;-2.27445;,
 -1.05850;-5.45060;-3.09739;,
 -0.29696;-2.23323;-1.10991;,
 -0.46482;-2.18092;-1.18176;,
 -0.10441;-2.40327;-1.48188;,
 -0.00810;-3.00328;-1.66787;,
 0.08815;-4.30324;-1.85379;,
 -0.26060;-4.56442;-1.85379;,
 -0.63814;-4.59844;-1.85379;,
 -1.00718;-4.61334;-1.85379;,
 -1.28320;-3.43965;-1.66933;,
 -1.21452;-2.96251;-1.48399;,
 -1.02302;-2.23323;-1.10991;,
 -0.69932;-2.18092;-1.18176;,
 -1.01527;-5.82046;-1.58364;,
 -0.98847;-5.90433;-1.77156;,
 -1.05973;-6.18645;-2.01016;,
 -1.26484;-6.40158;-2.19755;,
 -1.41446;-6.41818;-2.39075;,
 -1.73951;-6.35724;-2.45134;,
 -2.02960;-6.03923;-2.50865;,
 -2.21313;-5.79084;-2.32981;,
 -2.11735;-5.50086;-2.02506;,
 -2.27612;-6.26551;-1.63901;,
 -1.63599;-5.36614;-1.74535;,
 -1.50256;-5.30344;-1.69936;,
 -1.25733;-5.47963;-1.69356;,
 -2.18134;-6.21319;1.92000;,
 -2.28040;-6.08797;1.92077;,
 -2.27518;-6.08627;-1.59936;,
 -2.16861;-6.22094;-1.59830;,
 -2.28040;-6.08797;1.92077;,
 -2.27442;-5.92844;1.92000;,
 -2.26873;-5.91465;-1.59830;,
 -2.27518;-6.08627;-1.59936;,
 -2.08468;-6.02404;2.15755;,
 -2.14943;-6.15935;2.08822;,
 0.01601;-7.40131;2.08570;,
 0.77133;-7.49175;2.15755;,
 -2.14943;-6.15935;2.08822;,
 -0.01690;-7.45404;1.91209;,
 0.01601;-7.40131;2.08570;,
 0.94740;-7.88672;1.91209;,
 0.81174;-7.97305;1.91226;,
 0.81174;-7.97305;-1.60874;,
 0.94740;-7.88672;-1.60839;,
 -0.01690;-7.45404;-1.60839;,
 0.89684;-7.85053;2.08570;,
 2.30948;-5.91237;2.08446;,
 1.94525;-5.77958;2.15755;,
 0.89684;-7.85053;2.08570;,
 2.35963;-5.95870;1.89865;,
 2.30948;-5.91237;2.08446;,
 -1.35816;-1.10265;1.11870;,
 -1.03944;-0.25578;0.95793;,
 -1.03944;-0.25584;-0.65518;,
 -1.35816;-1.10265;-0.80744;,
 -0.62172;0.03350;0.68127;,
 -0.62172;0.03350;-0.37758;,
 -1.03944;-0.25584;-0.65518;,
 -0.81985;-1.10265;1.66979;,
 -1.29880;-1.10265;1.29166;,
 -1.28431;-2.00009;1.33794;,
 -0.78348;-2.00009;1.73384;,
 -1.34678;-2.00009;1.15524;,
 -0.91944;-0.25578;1.10263;,
 0.81561;-0.25578;1.10263;,
 0.51789;0.03350;0.68127;,
 0.58212;-1.10265;1.66979;,
 1.30735;-1.10265;0.86638;,
 1.06101;-1.10265;1.29166;,
 1.00042;-2.00009;1.33964;,
 1.25849;-2.00009;0.89670;,
 0.67872;-2.00009;1.73384;,
 0.93555;-0.25578;0.95787;,
 0.93555;-0.25578;-0.65424;,
 0.51789;0.03350;-0.37758;,
 0.93555;-0.25578;0.95787;,
 1.30735;-1.10265;-0.55435;,
 0.93555;-0.25578;-0.65424;,
 -1.29880;-1.10265;-0.98035;,
 -1.30044;-2.07141;-0.84492;,
 -1.34678;-2.00009;-0.72990;,
 -1.29880;-1.10265;-0.98035;,
 -1.09668;-1.10265;-1.17671;,
 -1.12730;-2.24367;-0.88439;,
 -1.30044;-2.07141;-0.84492;,
 -0.91903;-0.25578;-0.79888;,
 0.81555;-0.25578;-0.79888;,
 0.35865;-1.10265;-1.18997;,
 -2.14374;-6.16346;-1.77895;,
 0.01601;-7.40131;-1.78200;,
 -2.08468;-6.02404;-1.85379;,
 0.77133;-7.49175;-1.85379;,
 0.89684;-7.85053;-1.78200;,
 2.30936;-5.91237;-1.78077;,
 2.35963;-5.95870;-1.59490;,
 1.94525;-5.77958;-1.85379;,
 2.17441;-4.97340;1.89525;,
 2.42221;-5.81600;1.89666;,
 2.42239;-5.81653;-1.59496;,
 2.17493;-4.97551;-1.59490;,
 2.42221;-5.81600;1.89666;,
 2.42239;-5.81653;-1.59496;,
 2.11053;-4.99751;2.08329;,
 1.56882;-3.11478;2.08218;,
 1.42313;-3.15706;2.15755;,
 1.62912;-3.09724;1.90024;,
 2.11071;-4.99886;-1.78071;,
 1.57563;-3.13478;-1.77338;,
 1.62912;-3.09724;-1.57913;,
 2.11071;-4.99886;-1.78071;,
 1.44653;-3.22528;-1.85379;,
 1.57563;-3.13478;-1.77338;,
 0.45038;-2.06760;-1.25402;,
 1.25849;-2.00009;-0.58743;,
 -1.28730;-3.99602;2.15755;,
 1.52888;-2.90286;-1.45085;,
 1.38729;-2.62837;-1.26528;,
 -1.22842;-2.96691;-1.48382;,
 -1.50414;-4.05902;1.88903;,
 -1.50414;-4.05902;-1.54739;,
 -1.42994;-3.08844;-1.24322;,
 -1.46936;-3.60405;-1.42569;,
 -1.33446;-4.24829;-1.85379;,
 1.14594;-2.56345;-1.48188;,
 1.28764;-2.84451;-1.66787;,
 -2.21717;-5.95360;2.08810;,
 -1.44062;-4.04054;2.07889;,
 -1.37035;-3.02850;-1.41408;,
 -1.37035;-3.02850;-1.41408;,
 1.06101;-1.10265;-0.98035;,
 1.00212;-2.01980;-1.03407;,
 1.06101;-1.10265;-0.98035;,
 1.00212;-2.01980;-1.03407;,
 1.30113;-2.57541;-1.42059;,
 1.30113;-2.57541;-1.42059;,
 -1.41464;-3.53156;-1.59959;,
 -1.41464;-3.53156;-1.59959;,
 1.44260;-2.85172;-1.60628;,
 1.44260;-2.85172;-1.60628;,
 -2.21448;-5.94603;-1.77895;,
 -1.45446;-4.11444;-1.76406;,
 -2.21448;-5.94603;-1.77895;,
 -1.45446;-4.11444;-1.76406;,
 -2.24298;-6.07595;2.05760;,
 -2.24298;-6.07595;2.05760;,
 0.80423;-7.93487;2.05385;,
 0.80423;-7.93487;2.05385;,
 -1.27241;-0.98564;1.25987;,
 1.03468;-0.98564;1.25982;,
 -1.27223;-0.98564;-0.94903;,
 -1.27223;-0.98564;-0.94903;,
 1.03468;-0.98564;-0.94861;,
 1.03468;-0.98564;-0.94861;,
 -2.23958;-6.07454;-1.74617;,
 -2.23958;-6.07454;-1.74617;,
 0.80423;-7.93487;-1.75021;,
 2.38004;-5.80750;2.05009;,
 2.38004;-5.80750;2.05009;,
 2.38004;-5.80802;-1.74734;,
 2.38004;-5.80802;-1.74734;;
 
 188;
 3;0,1,2;,
 4;2,3,4,0;,
 4;5,6,7,2;,
 4;7,8,3,2;,
 3;6,9,7;,
 4;10,11,8,7;,
 3;12,13,3;,
 4;14,12,3,8;,
 3;11,15,8;,
 3;1,5,2;,
 3;3,13,4;,
 3;15,14,8;,
 3;9,10,7;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;34,33,32,35;,
 4;36,34,35,37;,
 4;37,38,39,36;,
 4;38,16,19,39;,
 4;40,38,37,41;,
 4;40,42,16,38;,
 4;42,43,17,16;,
 4;44,20,17,43;,
 4;45,22,20,44;,
 4;46,24,22,45;,
 4;47,26,24,46;,
 4;47,48,28,26;,
 4;48,49,30,28;,
 4;49,50,32,30;,
 4;35,32,50,51;,
 4;37,35,51,41;,
 4;21,23,52,53;,
 4;18,21,53,54;,
 4;19,18,54,55;,
 4;39,19,55,56;,
 4;36,39,56,57;,
 4;57,58,34,36;,
 4;58,59,33,34;,
 3;60,59,61;,
 3;62,60,61;,
 4;27,29,62,63;,
 4;25,27,63,64;,
 4;23,25,64,52;,
 4;53,52,10,9;,
 4;54,53,9,6;,
 4;55,54,6,5;,
 4;56,55,5,1;,
 4;57,56,1,0;,
 4;0,4,58,57;,
 4;4,13,59,58;,
 4;61,59,13,12;,
 4;62,61,12,14;,
 4;63,62,14,15;,
 4;64,63,15,11;,
 4;52,64,11,10;,
 4;65,66,67,68;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;77,65,78,79;,
 4;80,81,82,83;,
 4;81,78,84,82;,
 4;76,85,86,87;,
 4;88,80,89,90;,
 4;91,92,93,94;,
 4;92,95,96,97;,
 4;98,99,100,101;,
 4;99,91,102,100;,
 4;95,103,104,105;,
 4;103,98,106,104;,
 4;107,108,109,110;,
 4;108,106,111,109;,
 4;105,112,113,114;,
 4;115,107,116,117;,
 4;94,118,119,120;,
 4;121,122,123,124;,
 4;122,125,126,127;,
 4;125,96,114,126;,
 4;68,128,129,84;,
 4;128,130,131,129;,
 4;83,132,133,134;,
 4;132,131,135,133;,
 4;136,137,138,139;,
 4;140,89,134,141;,
 4;87,142,143,144;,
 4;142,136,145,143;,
 4;139,146,147,148;,
 4;149,135,150,151;,
 4;101,111,106,98;,
 3;95,114,96;,
 4;41,127,152,40;,
 4;80,83,134,89;,
 4;110,153,116,107;,
 4;120,102,91,94;,
 4;154,144,111,101;,
 3;148,155,145;,
 3;155,156,145;,
 3;156,153,145;,
 3;153,110,145;,
 4;123,50,49,157;,
 3;158,102,159;,
 3;102,120,159;,
 3;120,160,159;,
 3;160,161,159;,
 3;73,76,154;,
 3;154,76,144;,
 3;76,87,144;,
 4;136,139,148,145;,
 3;130,162,131;,
 3;162,47,131;,
 3;47,46,131;,
 3;46,45,131;,
 3;45,44,131;,
 3;44,150,131;,
 3;150,135,131;,
 4;71,70,158,159;,
 3;95,105,114;,
 4;68,84,78,65;,
 3;157,49,48;,
 3;48,47,162;,
 4;163,42,40,152;,
 4;164,43,42,163;,
 4;44,43,164,150;,
 4;70,165,166,158;,
 4;165,73,154,166;,
 4;120,119,167,160;,
 4;124,123,157,168;,
 4;127,169,170,152;,
 4;171,116,153,172;,
 4;158,166,100,102;,
 4;166,154,101,100;,
 4;144,143,109,111;,
 4;143,145,110,109;,
 4;152,170,173,163;,
 4;172,153,156,174;,
 4;160,167,175,161;,
 4;168,157,48,176;,
 4;148,147,177,155;,
 4;151,150,164,178;,
 4;130,179,180,162;,
 4;181,71,159,182;,
 4;163,173,178,164;,
 4;174,156,155,177;,
 4;162,180,176,48;,
 4;182,159,161,175;,
 4;165,70,69,183;,
 4;66,65,77,184;,
 4;74,73,165,183;,
 4;79,78,81,185;,
 4;81,80,88,185;,
 4;85,76,75,186;,
 3;103,95,92;,
 4;92,91,99,187;,
 4;99,98,103,187;,
 4;104,106,108,188;,
 4;108,107,115,188;,
 3;112,105,104;,
 4;125,122,121,189;,
 4;118,94,93,190;,
 3;97,125,189;,
 3;126,113,191;,
 4;117,116,171,192;,
 4;169,127,126,191;,
 4;72,71,181,193;,
 4;179,130,128,194;,
 4;128,68,67,194;,
 4;132,83,82,195;,
 4;82,84,129,195;,
 4;129,131,132,195;,
 4;142,87,86,196;,
 4;90,89,140,197;,
 4;137,136,142,196;,
 4;141,134,133,198;,
 4;133,135,149,198;,
 4;146,139,138,199;,
 3;126,114,113;,
 3;112,104,188;,
 3;103,92,187;,
 3;97,96,125;,
 4;122,127,41,51;,
 4;122,51,50,123;,
 4;29,31,60,62;,
 4;31,33,59,60;;
 
 MeshMaterialList {
  1;
  188;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  197;
  -0.096075;0.396647;-0.912930;,
  0.407849;-0.446770;0.796277;,
  -0.471921;0.314694;-0.823564;,
  0.049767;-0.282958;0.957840;,
  -0.200438;-0.418507;0.885820;,
  -0.462610;-0.098385;0.881086;,
  0.336088;-0.272311;0.901605;,
  0.016170;0.058005;0.998185;,
  -0.011644;0.599042;-0.800633;,
  -0.020769;0.644433;-0.764378;,
  0.887993;0.118729;-0.444266;,
  0.876259;0.018905;-0.481469;,
  -0.710846;0.353943;-0.607800;,
  0.716471;-0.237489;0.655948;,
  -0.312998;-0.205338;0.927291;,
  -0.207999;-0.216873;0.953783;,
  -0.041250;-0.512888;0.857464;,
  0.533414;-0.365216;0.762946;,
  0.738024;-0.301778;0.603532;,
  0.545829;-0.135629;0.826847;,
  0.377519;0.135820;0.915987;,
  0.107153;0.273738;0.955817;,
  -0.424110;0.354220;0.833462;,
  -0.634450;0.296495;0.713838;,
  -0.659276;0.081580;0.747462;,
  -0.487224;-0.287338;0.824652;,
  -0.343728;-0.393833;0.852494;,
  -0.136853;-0.475291;0.869120;,
  -0.316340;0.603350;-0.732050;,
  0.013359;0.589215;-0.807866;,
  0.592933;0.315685;-0.740792;,
  0.849850;-0.058739;-0.523741;,
  0.891550;-0.451749;-0.032582;,
  0.533511;-0.453223;0.714111;,
  0.184302;-0.262141;0.947267;,
  0.158661;0.905676;0.393163;,
  -0.154638;0.814749;0.558812;,
  -0.600698;0.601046;0.527167;,
  -0.691221;0.165596;0.703414;,
  -0.618380;0.536468;-0.574289;,
  0.760364;-0.250898;0.599080;,
  0.852244;-0.522879;0.016665;,
  0.825138;-0.431334;-0.364827;,
  0.645789;-0.335450;-0.685879;,
  -0.005452;0.003800;-0.999978;,
  -0.462418;0.196845;-0.864536;,
  -0.691533;0.157916;-0.704872;,
  -0.868510;0.329450;0.370342;,
  -0.726136;0.547770;0.415542;,
  -0.381597;0.649008;0.658158;,
  -0.023332;0.724408;0.688977;,
  0.403156;0.246432;0.881326;,
  0.818336;-0.435359;0.375219;,
  0.843351;-0.432987;0.318247;,
  0.811779;-0.583377;-0.026186;,
  0.526545;-0.725677;-0.442881;,
  0.158395;-0.725600;-0.669638;,
  -0.302922;-0.553996;-0.775452;,
  -0.671029;-0.280023;-0.686519;,
  -0.975984;0.157039;-0.150974;,
  -0.771612;0.398084;0.496130;,
  -0.522838;0.465469;0.714128;,
  -0.076797;0.419982;0.904277;,
  0.297813;0.345766;0.889805;,
  -0.937992;-0.306894;0.161205;,
  -0.636151;-0.753760;0.164796;,
  -0.511988;-0.527890;0.677643;,
  -0.284568;-0.073411;0.955841;,
  -0.756646;0.125147;0.641736;,
  -0.963163;0.219930;0.154754;,
  0.548290;-0.823667;0.144743;,
  0.681870;-0.713517;0.161083;,
  0.403776;-0.503667;0.763731;,
  -0.019272;-0.110573;0.993681;,
  -0.358013;-0.608521;0.708187;,
  -0.510370;-0.845959;0.154520;,
  -0.751297;0.610644;0.250332;,
  -0.972853;0.173825;0.152782;,
  -0.804681;0.197399;0.559930;,
  -0.320739;0.280037;0.904824;,
  -0.355320;0.667212;0.654657;,
  -0.203561;0.960688;0.188791;,
  0.762031;0.174261;0.623652;,
  0.951552;0.166167;0.258723;,
  0.742602;0.597041;0.303453;,
  0.255263;0.937460;0.236662;,
  0.371608;0.641964;0.670663;,
  0.349915;0.279595;0.894084;,
  -0.814738;0.137357;-0.563325;,
  -0.974195;0.162518;-0.156629;,
  -0.751292;0.609895;-0.252168;,
  -0.254780;0.937469;-0.237148;,
  -0.373054;0.642918;-0.668945;,
  -0.395974;0.119818;-0.910411;,
  0.743410;0.595696;-0.304117;,
  0.951805;0.166263;-0.257729;,
  0.618822;0.172844;-0.766279;,
  0.134496;0.137706;-0.981299;,
  0.306373;0.605919;-0.734165;,
  0.203558;0.960681;-0.188829;,
  -0.765526;0.124217;-0.631300;,
  -0.292854;-0.078026;-0.952968;,
  -0.528221;-0.535648;-0.658835;,
  -0.638685;-0.753820;-0.154393;,
  -0.940415;-0.307196;-0.145772;,
  -0.964024;0.220227;-0.148853;,
  0.548375;-0.823602;-0.144790;,
  -0.510896;-0.846184;-0.151518;,
  -0.360877;-0.612223;-0.703527;,
  -0.012252;-0.067180;-0.997666;,
  0.403833;-0.503492;-0.763816;,
  0.681904;-0.713469;-0.161149;,
  -0.215832;0.155703;0.963936;,
  -0.747065;0.277633;0.603998;,
  -0.953902;0.255979;0.156669;,
  0.591672;-0.289937;0.752237;,
  0.850451;-0.500144;0.163061;,
  0.984714;-0.069524;0.159701;,
  0.947131;0.279177;0.158121;,
  0.673001;0.202609;0.711350;,
  0.187779;0.015060;0.982096;,
  0.151851;0.202513;0.967435;,
  0.653683;0.427297;0.624593;,
  0.919180;0.382216;0.094971;,
  -0.986245;0.073710;-0.147945;,
  -0.723392;0.184144;-0.665429;,
  -0.519105;0.247989;-0.817943;,
  0.956633;0.226409;-0.183282;,
  0.619951;0.361238;-0.696540;,
  0.150212;0.354833;-0.922784;,
  0.589968;-0.292185;-0.752706;,
  0.190794;0.015407;-0.981509;,
  0.676280;0.203448;-0.707993;,
  0.947244;0.279647;-0.156610;,
  0.984382;-0.070956;-0.161110;,
  0.849699;-0.501290;-0.163462;,
  -0.320441;0.177009;0.930583;,
  -0.804189;0.140452;0.577540;,
  -0.989583;0.065578;0.128157;,
  0.947470;0.222525;0.229745;,
  0.729472;0.335072;0.596320;,
  0.298281;0.275929;0.913724;,
  0.865450;0.475836;-0.156772;,
  0.557812;0.644538;-0.522892;,
  0.120351;0.612155;-0.781525;,
  -0.975382;0.149119;-0.162459;,
  -0.705044;0.374992;-0.601908;,
  -0.367353;0.484807;-0.793734;,
  0.903642;0.399115;-0.155363;,
  0.637564;0.406861;-0.654199;,
  0.107598;0.189934;-0.975883;,
  -0.981483;0.173323;-0.081550;,
  -0.746725;0.251864;-0.615602;,
  -0.147127;0.132024;-0.980267;,
  0.845195;0.517437;-0.133808;,
  0.570739;0.615560;-0.543454;,
  0.123672;0.482339;-0.867211;,
  -0.977278;0.128856;-0.168298;,
  -0.796929;0.238470;-0.555010;,
  -0.800686;-0.262351;0.538585;,
  -0.368191;-0.601444;0.709014;,
  -0.740151;0.400752;0.539976;,
  0.717121;0.334034;0.611685;,
  -0.756025;0.397204;-0.520245;,
  0.637305;0.328872;-0.696911;,
  -0.819690;-0.267383;-0.506573;,
  0.548075;-0.785843;-0.286467;,
  0.662557;0.213887;0.717823;,
  0.944868;-0.075913;-0.318530;,
  -0.824412;0.435326;0.361714;,
  0.187165;0.975776;-0.113271;,
  -0.821310;0.219730;-0.526468;,
  -0.793357;0.436113;-0.424723;,
  0.889526;0.217189;-0.401960;,
  0.587361;-0.528427;0.613002;,
  -0.541076;0.465378;-0.700471;,
  -0.818601;0.361050;-0.446694;,
  0.465541;-0.660104;-0.589520;,
  -0.052968;-0.546968;-0.835476;,
  0.341187;0.333359;0.878899;,
  0.623417;-0.712214;-0.322648;,
  0.440218;-0.784373;-0.436998;,
  0.100294;-0.804566;-0.585333;,
  -0.324458;-0.670697;-0.667003;,
  -0.705770;-0.405027;-0.581242;,
  -0.809703;-0.297780;-0.505677;,
  -0.530707;-0.836741;0.134959;,
  -0.530717;-0.836729;-0.134997;,
  0.076269;0.068378;-0.994740;,
  0.000000;0.000000;-1.000000;,
  -0.026765;0.094304;-0.995184;,
  -0.259038;0.308917;-0.915134;,
  -0.046482;0.350471;-0.935419;,
  0.547918;-0.785986;0.286377;,
  -0.368100;-0.601326;-0.709161;,
  0.858030;-0.416626;0.300345;,
  0.242445;0.091064;-0.965882;;
  188;
  3;26,27,4;,
  4;4,5,25,26;,
  4;16,17,6,4;,
  4;6,7,5,4;,
  3;17,18,6;,
  4;19,20,7,6;,
  3;23,24,5;,
  4;22,23,5,7;,
  3;20,21,7;,
  3;27,16,4;,
  3;5,24,25;,
  3;21,22,7;,
  3;18,19,6;,
  4;30,31,42,43;,
  4;31,32,41,42;,
  4;32,33,40,41;,
  4;33,34,51,40;,
  4;170,35,50,170;,
  4;35,36,49,50;,
  4;36,37,48,49;,
  4;37,38,47,48;,
  4;46,171,172,39;,
  4;45,46,39,28;,
  4;28,29,44,45;,
  4;29,30,43,44;,
  4;8,29,28,0;,
  4;8,9,30,29;,
  4;173,10,31,30;,
  4;11,32,31,10;,
  4;1,33,32,174;,
  4;3,34,33,1;,
  4;15,15,34,3;,
  4;15,14,14,15;,
  4;13,13,13,13;,
  4;175,12,172,176;,
  4;39,172,12,2;,
  4;28,39,2,0;,
  4;41,40,52,53;,
  4;42,41,53,54;,
  4;43,42,54,55;,
  4;177,43,55,56;,
  4;178,44,56,57;,
  4;57,58,46,45;,
  4;58,59,171,46;,
  3;169,59,60;,
  3;61,169,60;,
  4;50,49,61,62;,
  4;51,50,62,63;,
  4;40,51,63,179;,
  4;53,52,19,18;,
  4;54,53,18,17;,
  4;55,54,180,181;,
  4;56,55,181,182;,
  4;57,56,182,183;,
  4;183,184,58,57;,
  4;184,185,59,58;,
  4;60,59,24,23;,
  4;61,60,23,22;,
  4;62,61,22,21;,
  4;63,62,21,20;,
  4;179,63,20,19;,
  4;65,64,104,103;,
  4;64,69,105,104;,
  4;67,66,74,73;,
  4;66,65,75,74;,
  4;71,70,106,111;,
  4;186,75,107,187;,
  4;73,72,115,120;,
  4;72,71,116,115;,
  4;77,76,90,89;,
  4;76,81,91,90;,
  4;79,78,137,136;,
  4;78,77,138,137;,
  4;81,80,86,85;,
  4;80,79,87,86;,
  4;83,82,140,139;,
  4;82,87,141,140;,
  4;85,84,94,99;,
  4;84,83,95,94;,
  4;89,88,125,124;,
  4;88,93,126,125;,
  4;93,92,98,97;,
  4;92,91,99,98;,
  4;103,102,108,107;,
  4;102,101,109,108;,
  4;111,110,130,135;,
  4;110,109,131,130;,
  4;118,117,134,133;,
  4;117,116,135,134;,
  4;120,119,122,121;,
  4;119,118,123,122;,
  4;133,132,149,148;,
  4;132,131,150,149;,
  4;136,141,87,79;,
  3;81,99,91;,
  4;0,97,129,8;,
  4;71,111,135,116;,
  4;139,127,95,83;,
  4;124,138,77,89;,
  4;112,121,141,136;,
  3;148,154,123;,
  3;154,142,123;,
  3;142,127,123;,
  3;127,139,123;,
  4;126,12,175,147;,
  3;114,138,151;,
  3;138,124,151;,
  3;124,145,151;,
  3;145,157,151;,
  3;67,73,112;,
  3;112,73,121;,
  3;73,120,121;,
  4;118,133,148,123;,
  3;101,153,109;,
  3;153,188,109;,
  3;188,189,109;,
  3;189,189,109;,
  3;189,190,109;,
  3;190,150,109;,
  3;150,131,109;,
  4;105,69,114,151;,
  3;81,85,99;,
  4;103,107,75,65;,
  3;147,175,191;,
  3;191,188,153;,
  4;144,9,8,129;,
  4;156,192,9,144;,
  4;190,192,156,150;,
  4;69,68,113,114;,
  4;68,67,112,113;,
  4;124,125,146,145;,
  4;125,126,147,146;,
  4;97,96,128,129;,
  4;96,95,127,128;,
  4;114,113,137,138;,
  4;113,112,136,137;,
  4;121,122,140,141;,
  4;122,123,139,140;,
  4;129,128,143,144;,
  4;128,127,142,143;,
  4;145,146,158,157;,
  4;146,147,191,158;,
  4;148,149,155,154;,
  4;149,150,156,155;,
  4;101,100,152,153;,
  4;100,105,151,152;,
  4;144,143,155,156;,
  4;143,142,154,155;,
  4;153,152,158,191;,
  4;152,151,157,158;,
  4;68,69,64,159;,
  4;64,65,66,159;,
  4;66,67,68,159;,
  4;74,75,186,160;,
  4;70,71,72,193;,
  4;72,73,74,160;,
  3;80,81,76;,
  4;76,77,78,161;,
  4;78,79,80,161;,
  4;86,87,82,162;,
  4;82,83,84,162;,
  3;84,85,86;,
  4;92,93,88,163;,
  4;88,89,90,163;,
  3;90,92,163;,
  3;98,94,164;,
  4;94,95,96,164;,
  4;96,97,98,164;,
  4;104,105,100,165;,
  4;100,101,102,165;,
  4;102,103,104,165;,
  4;110,111,106,166;,
  4;187,107,108,194;,
  4;108,109,110,194;,
  4;119,120,115,167;,
  4;115,116,117,195;,
  4;117,118,119,167;,
  4;134,135,130,168;,
  4;130,131,132,196;,
  4;132,133,134,168;,
  3;98,99,94;,
  3;84,86,162;,
  3;80,76,161;,
  3;90,91,92;,
  4;93,97,0,2;,
  4;93,2,12,126;,
  4;49,48,169,61;,
  4;48,47,59,169;;
 }
 MeshTextureCoords {
  200;
  0.500000;0.634120;,
  0.531250;0.634120;,
  0.500000;0.638750;,
  0.443820;0.638850;,
  0.440660;0.634170;,
  0.531250;0.638750;,
  0.531250;0.643380;,
  0.500000;0.643380;,
  0.446930;0.643450;,
  0.531250;0.645690;,
  0.500000;0.645690;,
  0.448460;0.645730;,
  0.426600;0.638820;,
  0.425040;0.634170;,
  0.428930;0.643430;,
  0.429710;0.645730;,
  0.545490;0.638750;,
  0.545490;0.643380;,
  0.542670;0.643380;,
  0.542670;0.638750;,
  0.545490;0.646750;,
  0.542670;0.646540;,
  0.500000;0.646750;,
  0.500000;0.646540;,
  0.449160;0.646760;,
  0.449020;0.646560;,
  0.421870;0.646760;,
  0.423420;0.646560;,
  0.420730;0.643420;,
  0.422350;0.643420;,
  0.418750;0.638810;,
  0.420300;0.638820;,
  0.416470;0.632040;,
  0.418170;0.632460;,
  0.439510;0.632460;,
  0.439220;0.632040;,
  0.500000;0.632430;,
  0.500000;0.632010;,
  0.545490;0.632010;,
  0.542670;0.632430;,
  0.562500;0.629490;,
  0.500000;0.629490;,
  0.562500;0.638750;,
  0.562500;0.643380;,
  0.562500;0.648010;,
  0.500000;0.648010;,
  0.450000;0.648010;,
  0.412500;0.648010;,
  0.410940;0.643410;,
  0.409370;0.638800;,
  0.406250;0.629490;,
  0.437500;0.629490;,
  0.500000;0.646250;,
  0.538800;0.646250;,
  0.538800;0.643380;,
  0.538800;0.638750;,
  0.538800;0.633000;,
  0.500000;0.633000;,
  0.439900;0.633040;,
  0.420500;0.633040;,
  0.421370;0.638820;,
  0.422430;0.638820;,
  0.424580;0.643430;,
  0.425550;0.646280;,
  0.448830;0.646280;,
  0.381610;0.985190;,
  0.375000;0.990560;,
  0.375000;0.760020;,
  0.382110;0.765920;,
  0.365560;-0.000000;,
  0.360200;0.009050;,
  0.140920;0.009740;,
  0.135020;-0.000000;,
  0.382200;0.009860;,
  0.379050;-0.000000;,
  0.495120;-0.000000;,
  0.499050;0.006520;,
  0.379050;1.000000;,
  0.493170;0.984700;,
  0.495120;1.000000;,
  0.509210;0.984700;,
  0.501650;0.985070;,
  0.501650;0.764910;,
  0.509210;0.765300;,
  0.493170;0.765300;,
  0.507200;-0.000000;,
  0.618980;-0.000000;,
  0.612940;0.009690;,
  0.507200;1.000000;,
  0.617430;0.983870;,
  0.618980;1.000000;,
  0.349690;0.244110;,
  0.250000;0.375000;,
  0.133710;0.258710;,
  0.150310;0.244110;,
  0.395450;0.275310;,
  0.395450;0.474690;,
  0.366290;0.491290;,
  0.395450;0.244110;,
  0.373130;0.244320;,
  0.375000;0.120510;,
  0.395580;0.120510;,
  0.349410;0.120510;,
  0.395140;0.254610;,
  0.604860;0.254610;,
  0.604550;0.275310;,
  0.604550;0.244110;,
  0.650310;0.244110;,
  0.626870;0.244310;,
  0.625000;0.120510;,
  0.650010;0.120510;,
  0.604300;0.120510;,
  0.625000;0.266370;,
  0.625000;0.483640;,
  0.604550;0.474690;,
  0.641370;0.250000;,
  0.849690;0.244110;,
  0.858640;0.250000;,
  0.125000;0.245370;,
  0.125000;0.120510;,
  0.162650;0.120510;,
  0.375000;0.504630;,
  0.395450;0.505890;,
  0.390260;0.629490;,
  0.375000;0.629490;,
  0.395190;0.495390;,
  0.604860;0.495390;,
  0.604550;0.505890;,
  0.381070;0.749320;,
  0.498800;0.750540;,
  0.382200;0.740140;,
  0.504690;0.742310;,
  0.509260;0.751110;,
  0.616000;0.749620;,
  0.617430;0.766130;,
  0.612940;0.740310;,
  0.641350;0.006170;,
  0.635600;-0.000000;,
  0.864460;-0.000000;,
  0.858870;0.006090;,
  0.625000;0.989400;,
  0.625000;0.760540;,
  0.624910;0.006830;,
  0.625000;0.101990;,
  0.609450;0.101990;,
  0.641040;0.101990;,
  0.875000;0.005140;,
  0.875000;0.101990;,
  0.857880;0.101990;,
  0.625000;0.744850;,
  0.618370;0.648010;,
  0.625000;0.648010;,
  0.616540;0.629490;,
  0.849350;0.120510;,
  0.391360;0.101990;,
  0.858100;0.105280;,
  0.858130;0.109910;,
  0.407100;0.638800;,
  0.358270;0.101990;,
  0.144100;0.101990;,
  0.150750;0.110720;,
  0.141440;0.106090;,
  0.387810;0.648010;,
  0.617320;0.638750;,
  0.617540;0.643380;,
  0.373130;0.006160;,
  0.375000;0.101990;,
  0.125000;0.111250;,
  0.375000;0.638750;,
  0.625000;0.504690;,
  0.625000;0.629490;,
  0.875000;0.245310;,
  0.875000;0.120510;,
  0.625000;0.638750;,
  0.875000;0.111250;,
  0.125000;0.106620;,
  0.375000;0.643380;,
  0.875000;0.106620;,
  0.625000;0.643380;,
  0.375000;0.744390;,
  0.375000;0.648010;,
  0.125000;0.005620;,
  0.125000;0.101990;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.375000;0.500000;,
  0.125000;0.250000;,
  0.625000;0.500000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.875000;0.000000;;
 }
}
