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
 145;
 1.52683;-4.35935;3.32865;,
 1.76698;-2.28075;2.87565;,
 -0.05657;-2.28075;2.87565;,
 -0.05657;-4.35935;3.32865;,
 3.11008;-4.35935;-1.30345;,
 3.59048;-2.28075;-0.85045;,
 3.59048;-2.28075;0.02000;,
 3.11008;-4.35935;0.02000;,
 -0.05657;-4.35935;-3.28865;,
 -0.05657;-2.28075;-2.83565;,
 1.76698;-2.28075;-2.83565;,
 1.52683;-4.35935;-3.28865;,
 -3.22317;-4.35935;0.02000;,
 -3.36737;-2.28075;0.02000;,
 -3.36737;-2.28075;-1.30345;,
 -3.22317;-4.35935;-1.30345;,
 1.18163;-9.64866;-0.99315;,
 1.18163;-9.64866;0.02000;,
 -0.05657;-9.64866;0.02000;,
 -0.05657;-9.64866;-0.99315;,
 1.76698;2.91600;0.02000;,
 1.76698;2.91600;-1.30345;,
 -0.05657;2.91600;-1.30345;,
 -0.05657;2.91600;0.02000;,
 -3.70357;0.31765;0.02000;,
 -3.70357;0.31765;-1.30345;,
 -0.05657;0.31765;-3.28865;,
 1.76698;0.31765;-3.28865;,
 3.59048;0.31765;-1.30345;,
 3.59048;0.31765;0.02000;,
 1.76698;0.31765;3.32865;,
 -0.05657;0.31765;3.32865;,
 -2.80412;2.63990;-1.30345;,
 -3.61952;1.74850;-1.30345;,
 -3.65247;1.74235;0.02000;,
 -2.81247;2.63990;0.02000;,
 1.76698;2.13945;-2.46480;,
 -0.05657;2.27630;-2.46480;,
 3.43678;2.23495;0.02000;,
 3.34368;2.21315;-1.30345;,
 -0.05657;2.27630;2.50480;,
 1.76698;2.13945;2.50480;,
 1.18163;-8.85680;2.56695;,
 1.32488;-6.89965;2.99950;,
 -0.05657;-6.89965;2.99950;,
 -0.05657;-8.85680;2.56695;,
 2.41978;-8.85680;-0.99315;,
 2.70638;-6.89965;-1.24820;,
 2.70638;-6.89965;0.02000;,
 2.41978;-8.85680;0.02000;,
 -0.05657;-8.85680;-2.52695;,
 -0.05657;-6.89965;-2.95950;,
 1.32488;-6.89965;-2.95950;,
 1.18163;-8.85680;-2.52695;,
 -2.53292;-8.85680;0.02000;,
 -2.81947;-6.89965;0.02000;,
 -2.81947;-6.89965;-1.24820;,
 -2.53292;-8.85680;-0.99315;,
 2.90508;1.79905;2.25760;,
 2.90508;0.31765;2.93345;,
 3.59048;0.31765;1.34345;,
 3.34368;2.21315;1.34345;,
 3.59048;-2.28075;0.89045;,
 2.90508;-2.28075;2.50900;,
 3.11008;-4.35935;1.34345;,
 2.51498;-4.35935;2.93345;,
 2.41978;-8.85680;1.03310;,
 2.70638;-6.89965;1.28820;,
 2.18708;-6.89965;2.60615;,
 1.95438;-8.85680;2.17330;,
 -0.05657;-9.64866;1.03310;,
 1.18163;-9.64866;1.03310;,
 -2.20937;-6.89965;2.78235;,
 -2.81947;-6.89965;1.28820;,
 -2.53292;-8.85680;1.03310;,
 -1.98607;-8.85680;2.20285;,
 -2.56202;-2.28075;3.14575;,
 -3.36737;-2.28075;1.34345;,
 -3.22317;-4.35935;1.34345;,
 -2.52392;-4.35935;3.32865;,
 -2.89827;0.31765;3.32865;,
 -3.70357;0.31765;1.34345;,
 -2.84047;1.81980;2.50480;,
 1.76698;2.91600;1.34345;,
 -0.05657;2.91600;1.34345;,
 -2.84047;1.81980;-2.46480;,
 -2.89827;0.31765;-3.28865;,
 -2.56202;-2.28075;-3.10575;,
 -2.52392;-4.35935;-3.28865;,
 -2.20937;-6.89965;-2.74235;,
 -1.98607;-8.85680;-2.16285;,
 1.18163;-8.85680;-2.52695;,
 -0.05657;-8.85680;-2.52695;,
 2.18708;-6.89965;-2.56615;,
 1.95438;-8.85680;-2.13330;,
 2.90508;-2.28075;-2.46900;,
 2.51498;-4.35935;-2.89345;,
 2.90508;0.31765;-2.89345;,
 2.90508;1.79905;-2.21760;,
 -0.05657;2.27630;-2.46480;,
 1.76698;2.13945;-2.46480;,
 -3.61952;1.74850;1.34345;,
 -2.80412;2.63990;1.34345;,
 -1.88007;2.15635;2.50480;,
 -1.88007;0.31765;3.32865;,
 -1.88007;-2.28075;3.14575;,
 -1.63987;-4.35935;3.32865;,
 -1.43802;-6.89965;2.99950;,
 -1.29472;-8.85680;2.56695;,
 -1.29472;-9.64866;1.03310;,
 -1.29472;-9.64866;0.02000;,
 -1.29472;-9.64866;-0.99315;,
 -1.29472;-8.85680;-2.52695;,
 -1.29472;-8.85680;-2.52695;,
 -1.43802;-6.89965;-2.95950;,
 -1.63987;-4.35935;-3.28865;,
 -1.88007;-2.28075;-3.10575;,
 -1.88007;0.31765;-3.28865;,
 -1.88007;2.15635;-2.46480;,
 -1.88007;2.15635;-2.46480;,
 -1.88007;2.91600;-1.30345;,
 -1.88007;2.91600;0.02000;,
 -1.88007;2.91600;1.34345;,
 1.95438;-8.85680;-2.13330;,
 2.41978;-8.85680;0.02000;,
 2.41978;-8.85680;-0.99315;,
 2.41978;-8.85680;1.03310;,
 3.43678;2.23495;0.02000;,
 3.34368;2.21315;1.34345;,
 3.34368;2.21315;-1.30345;,
 2.90508;1.79905;-2.21760;,
 -2.84047;1.81980;2.50480;,
 -2.89827;0.31765;3.32865;,
 -2.56202;-2.28075;3.14575;,
 -2.52392;-4.35935;3.32865;,
 -2.20937;-6.89965;2.78235;,
 -1.98607;-8.85680;2.20285;,
 -2.53292;-8.85680;1.03310;,
 -2.53292;-8.85680;0.02000;,
 -2.53292;-8.85680;-0.99315;,
 -1.98607;-8.85680;-2.16285;,
 -2.84047;1.81980;-2.46480;,
 -2.80412;2.63990;-1.30345;,
 -2.81247;2.63990;0.02000;,
 -2.80412;2.63990;1.34345;;
 
 124;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;13,24,25,14;,
 4;9,26,27,10;,
 4;5,28,29,6;,
 4;1,30,31,2;,
 4;32,33,34,35;,
 4;36,27,26,37;,
 4;38,29,28,39;,
 4;40,31,30,41;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,60,59,63;,
 4;64,62,63,65;,
 4;66,67,68,69;,
 4;45,70,71,42;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,77,76;,
 3;82,81,80;,
 4;41,83,84,40;,
 3;85,33,32;,
 4;14,25,86,87;,
 4;15,14,87,88;,
 4;57,56,89,90;,
 4;91,16,19,92;,
 4;93,47,46,94;,
 4;95,5,4,96;,
 4;97,28,5,95;,
 4;39,28,97,98;,
 4;99,22,21,100;,
 4;35,34,101,102;,
 4;77,81,24,13;,
 4;78,77,13,12;,
 4;74,73,55,54;,
 4;17,71,70,18;,
 4;49,48,67,66;,
 4;7,6,62,64;,
 4;6,29,60,62;,
 4;61,60,29,38;,
 4;83,20,23,84;,
 4;103,104,31,40;,
 4;2,31,104,105;,
 4;3,2,105,106;,
 4;45,44,107,108;,
 4;108,109,70,45;,
 4;18,70,109,110;,
 4;19,18,110,111;,
 4;92,19,111,112;,
 4;113,114,51,50;,
 4;115,116,9,8;,
 4;116,117,26,9;,
 4;37,26,117,118;,
 4;119,120,22,99;,
 4;23,22,120,121;,
 4;84,23,121,122;,
 4;40,84,122,103;,
 4;98,97,27,36;,
 4;10,27,97,95;,
 4;11,10,95,96;,
 4;53,52,93,94;,
 3;123,16,91;,
 4;124,17,16,125;,
 4;126,71,17,124;,
 3;69,71,126;,
 4;68,43,42,69;,
 4;63,1,0,65;,
 4;59,30,1,63;,
 4;41,30,59,58;,
 3;58,83,41;,
 4;127,20,83,128;,
 4;129,21,20,127;,
 3;130,21,129;,
 4;131,132,104,103;,
 4;105,104,132,133;,
 4;106,105,133,134;,
 4;108,107,135,136;,
 3;136,109,108;,
 4;110,109,137,138;,
 4;111,110,138,139;,
 3;140,111,139;,
 4;89,114,113,90;,
 4;87,116,115,88;,
 4;86,117,116,87;,
 4;118,117,86,85;,
 4;141,142,120,119;,
 4;121,120,142,143;,
 4;122,121,143,144;,
 4;103,122,144,131;,
 3;112,111,140;,
 3;136,137,109;,
 3;125,16,123;,
 3;42,71,69;,
 3;85,86,25;,
 3;102,101,82;,
 3;85,25,33;,
 4;34,33,25,24;,
 4;101,34,24,81;,
 3;82,101,81;,
 4;79,78,73,72;,
 4;55,73,78,12;,
 4;56,55,12,15;,
 4;89,56,15,88;,
 4;88,115,114,89;,
 4;51,114,115,8;,
 4;52,51,8,11;,
 4;93,52,11,96;,
 4;96,4,47,93;,
 4;48,47,4,7;,
 4;67,48,7,64;,
 4;68,67,64,65;,
 4;65,0,43,68;,
 4;44,43,0,3;,
 4;107,44,3,106;,
 4;135,107,106,134;,
 3;100,21,130;,
 3;128,83,58;;
 
 MeshMaterialList {
  1;
  124;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  127;
  -0.725175;0.462695;0.509936;,
  -0.567522;-0.605064;0.558404;,
  0.514828;0.572560;0.638065;,
  0.592467;-0.597949;0.539852;,
  0.514828;0.572560;-0.638065;,
  0.592466;-0.597944;-0.539859;,
  -0.615728;0.482688;-0.622809;,
  -0.567522;-0.605059;-0.558411;,
  -0.921621;-0.079058;0.379954;,
  -0.921621;-0.079058;-0.379954;,
  0.686850;-0.053231;-0.724847;,
  0.686850;-0.053231;0.724847;,
  -0.922058;0.052312;0.383501;,
  -0.922058;0.052312;-0.383501;,
  0.675647;0.087993;-0.731955;,
  0.675647;0.087993;0.731955;,
  -0.927366;-0.097754;0.361159;,
  0.706023;-0.078298;0.703848;,
  0.706023;-0.078298;-0.703848;,
  -0.927366;-0.097754;-0.361159;,
  0.994517;0.104574;0.000000;,
  0.998629;0.052342;0.000000;,
  0.993558;-0.113321;-0.000000;,
  0.981555;-0.191181;-0.000000;,
  0.839950;-0.542663;-0.000000;,
  -0.839952;-0.542661;0.000000;,
  -0.993574;-0.113188;0.000000;,
  -0.995107;-0.098806;0.000000;,
  -0.999171;-0.040698;0.000000;,
  -0.528349;0.849027;0.000000;,
  -0.520329;0.814357;-0.257060;,
  -0.961611;0.014643;-0.274027;,
  -0.976894;-0.090655;-0.193544;,
  -0.977135;-0.107304;-0.183554;,
  -0.814284;-0.553147;-0.175980;,
  0.819060;-0.550855;-0.160312;,
  0.968687;-0.167021;-0.183708;,
  0.975416;-0.103972;-0.194302;,
  0.974340;0.047243;-0.220069;,
  0.842552;0.389018;-0.372520;,
  -0.520329;0.814357;0.257060;,
  -0.961611;0.014643;0.274027;,
  -0.976894;-0.090655;0.193544;,
  -0.977135;-0.107304;0.183554;,
  -0.814285;-0.553149;0.175975;,
  0.819060;-0.550856;0.160308;,
  0.968687;-0.167021;0.183708;,
  0.975416;-0.103972;0.194302;,
  0.974340;0.047243;0.220069;,
  0.842552;0.389018;0.372520;,
  0.001432;0.658402;0.752665;,
  0.019328;0.131636;0.991110;,
  0.036965;0.020169;0.999113;,
  0.018537;0.029078;0.999405;,
  0.000000;-0.609851;0.792516;,
  0.000000;-0.971745;0.236034;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.971743;-0.236040;,
  0.000000;-0.609846;-0.792520;,
  0.018537;0.029078;-0.999405;,
  0.036965;0.020169;-0.999113;,
  0.019328;0.131636;-0.991110;,
  0.001432;0.658402;-0.752665;,
  0.000951;0.963270;-0.268534;,
  0.000000;1.000000;0.000000;,
  0.000951;0.963270;0.268534;,
  0.183611;0.640715;-0.745501;,
  0.166711;0.122536;-0.978362;,
  0.167059;0.007649;-0.985917;,
  0.186760;0.019030;-0.982221;,
  0.181081;-0.614070;-0.768197;,
  0.272774;-0.932579;-0.236411;,
  0.280673;-0.959804;-0.000000;,
  0.272772;-0.932582;0.236404;,
  0.181080;-0.614076;0.768193;,
  0.186760;0.019030;0.982221;,
  0.167059;0.007649;0.985917;,
  0.166711;0.122535;0.978362;,
  0.183611;0.640715;0.745501;,
  0.235488;0.912952;0.333263;,
  0.200268;0.979741;-0.000000;,
  0.235488;0.912952;-0.333263;,
  -0.097113;0.654335;0.749943;,
  -0.002965;0.169159;0.985584;,
  0.036676;0.014031;0.999229;,
  -0.015755;-0.015506;0.999756;,
  -0.163639;-0.618227;0.768777;,
  -0.273458;-0.930839;0.242404;,
  -0.280664;-0.959806;0.000000;,
  -0.273459;-0.930837;-0.242411;,
  -0.163640;-0.618221;-0.768781;,
  -0.015755;-0.015506;-0.999756;,
  0.036676;0.014031;-0.999229;,
  -0.002965;0.169159;-0.985584;,
  -0.097113;0.654335;-0.749943;,
  -0.150189;0.949019;-0.277138;,
  -0.144057;0.989569;0.000000;,
  -0.150189;0.949020;0.277138;,
  -0.884563;0.379961;-0.270514;,
  -0.922251;0.386591;0.000000;,
  -0.884563;0.379961;0.270514;,
  -0.645115;-0.226782;0.729655;,
  -0.966984;-0.170618;0.189294;,
  -0.988547;-0.150911;0.000000;,
  -0.966983;-0.170617;-0.189296;,
  -0.645114;-0.226781;-0.729656;,
  -0.124485;-0.199677;-0.971922;,
  0.000000;-0.172319;-0.985041;,
  0.207479;-0.188353;-0.959935;,
  0.711855;-0.198038;-0.673828;,
  0.969277;-0.164247;-0.183097;,
  0.988546;-0.150923;-0.000000;,
  0.969277;-0.164248;0.183096;,
  0.711856;-0.198039;0.673826;,
  0.207479;-0.188353;0.959935;,
  0.000000;-0.172319;0.985041;,
  -0.124485;-0.199677;0.971922;,
  0.392462;0.919768;-0.000000;,
  0.392376;0.919567;0.020899;,
  0.392376;0.919567;-0.020899;,
  -0.071156;0.444296;0.893050;,
  -0.036896;0.193970;0.980313;,
  -0.000000;0.008746;0.999962;,
  -0.068461;-0.046303;0.996579;,
  -0.000000;0.008746;-0.999962;,
  -0.068461;-0.046303;-0.996579;,
  -0.036896;0.193970;-0.980313;;
  124;
  4;75,76,52,53;,
  4;36,37,22,23;,
  4;59,60,68,69;,
  4;26,27,32,33;,
  4;71,72,56,57;,
  4;80,81,63,64;,
  4;27,28,31,32;,
  4;60,61,67,68;,
  4;37,38,21,22;,
  4;76,77,51,52;,
  4;30,98,99,29;,
  4;66,67,61,62;,
  4;20,21,38,39;,
  4;50,51,77,78;,
  4;74,114,115,54;,
  4;35,110,111,24;,
  4;58,107,108,70;,
  4;25,103,104,34;,
  4;2,15,48,49;,
  4;47,48,15,11;,
  4;46,47,11,17;,
  4;45,112,113,3;,
  4;54,55,73,74;,
  4;101,102,44,1;,
  4;8,42,43,16;,
  4;12,41,42,8;,
  3;0,41,12;,
  4;78,79,65,50;,
  3;6,98,30;,
  4;32,31,13,9;,
  4;33,32,9,19;,
  4;34,104,105,7;,
  4;70,71,57,58;,
  4;109,110,35,5;,
  4;10,37,36,18;,
  4;14,38,37,10;,
  4;39,38,14,4;,
  4;62,63,81,66;,
  4;29,99,100,40;,
  4;42,41,28,27;,
  4;43,42,27,26;,
  4;44,102,103,25;,
  4;72,73,55,56;,
  4;24,111,112,45;,
  4;23,22,47,46;,
  4;22,21,48,47;,
  4;49,48,21,20;,
  4;79,80,64,65;,
  4;82,83,51,50;,
  4;52,51,83,84;,
  4;53,52,84,85;,
  4;54,115,116,86;,
  4;86,87,55,54;,
  4;56,55,87,88;,
  4;57,56,88,89;,
  4;58,57,89,90;,
  4;90,106,107,58;,
  4;91,92,60,59;,
  4;92,93,61,60;,
  4;62,61,93,94;,
  4;94,95,63,62;,
  4;64,63,95,96;,
  4;65,64,96,97;,
  4;50,65,97,82;,
  4;4,14,67,66;,
  4;68,67,14,10;,
  4;69,68,10,18;,
  4;70,108,109,5;,
  3;5,71,70;,
  4;24,72,71,35;,
  4;45,73,72,24;,
  3;3,73,45;,
  4;113,114,74,3;,
  4;11,76,75,17;,
  4;15,77,76,11;,
  4;78,77,15,2;,
  3;2,79,78;,
  4;117,80,79,118;,
  4;119,81,80,117;,
  3;4,81,39;,
  4;120,121,83,82;,
  4;84,83,121,122;,
  4;85,84,122,123;,
  4;86,116,101,1;,
  3;1,87,86;,
  4;88,87,44,25;,
  4;89,88,25,34;,
  3;7,89,34;,
  4;105,106,90,7;,
  4;124,92,91,125;,
  4;126,93,92,124;,
  4;94,93,126,6;,
  4;6,30,95,94;,
  4;96,95,30,29;,
  4;97,96,29,40;,
  4;82,97,40,0;,
  3;90,89,7;,
  3;1,44,87;,
  3;35,71,5;,
  3;74,73,3;,
  3;6,13,31;,
  3;40,100,0;,
  3;6,31,98;,
  4;99,98,31,28;,
  4;100,99,28,41;,
  3;0,100,41;,
  4;16,43,102,101;,
  4;103,102,43,26;,
  4;104,103,26,33;,
  4;105,104,33,19;,
  4;125,91,106,105;,
  4;107,106,91,59;,
  4;108,107,59,69;,
  4;109,108,69,18;,
  4;18,36,110,109;,
  4;111,110,36,23;,
  4;112,111,23,46;,
  4;113,112,46,17;,
  4;17,75,114,113;,
  4;115,114,75,53;,
  4;116,115,53,85;,
  4;101,116,85,123;,
  3;66,81,4;,
  3;49,79,2;;
 }
 MeshTextureCoords {
  145;
  0.550000;0.187500;,
  0.500000;0.187500;,
  0.500000;0.125000;,
  0.550000;0.125000;,
  0.550000;0.425000;,
  0.500000;0.425000;,
  0.500000;0.375000;,
  0.550000;0.375000;,
  0.550000;0.625000;,
  0.500000;0.625000;,
  0.500000;0.562500;,
  0.550000;0.562500;,
  0.550000;0.875000;,
  0.500000;0.875000;,
  0.500000;0.825000;,
  0.550000;0.825000;,
  0.800000;0.187500;,
  0.750000;0.187500;,
  0.750000;0.125000;,
  0.800000;0.125000;,
  0.250000;0.187500;,
  0.200000;0.187500;,
  0.200000;0.125000;,
  0.250000;0.125000;,
  0.437500;0.875000;,
  0.437500;0.825000;,
  0.437500;0.625000;,
  0.437500;0.562500;,
  0.437500;0.425000;,
  0.437500;0.375000;,
  0.437500;0.187500;,
  0.437500;0.125000;,
  0.375000;0.825000;,
  0.404250;0.825000;,
  0.406250;0.875000;,
  0.375000;0.875000;,
  0.375000;0.562500;,
  0.375000;0.625000;,
  0.375000;0.375000;,
  0.375000;0.425000;,
  0.375000;0.125000;,
  0.375000;0.187500;,
  0.625000;0.187500;,
  0.590100;0.187500;,
  0.590100;0.125000;,
  0.625000;0.125000;,
  0.625000;0.425000;,
  0.590100;0.425000;,
  0.590100;0.375000;,
  0.625000;0.375000;,
  0.625000;0.625000;,
  0.590100;0.625000;,
  0.590100;0.562500;,
  0.625000;0.562500;,
  0.625000;0.875000;,
  0.590100;0.875000;,
  0.590100;0.825000;,
  0.625000;0.825000;,
  0.375000;0.250000;,
  0.437500;0.250000;,
  0.437500;0.325000;,
  0.375000;0.325000;,
  0.500000;0.325000;,
  0.500000;0.250000;,
  0.550000;0.325000;,
  0.550000;0.250000;,
  0.625000;0.325000;,
  0.590100;0.325000;,
  0.590100;0.250000;,
  0.625000;0.250000;,
  0.700000;0.125000;,
  0.700000;0.187500;,
  0.590100;1.000000;,
  0.590100;0.925000;,
  0.625000;0.925000;,
  0.625000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.925000;,
  0.550000;0.925000;,
  0.550000;1.000000;,
  0.437500;1.000000;,
  0.437500;0.925000;,
  0.375000;1.000000;,
  0.300000;0.187500;,
  0.300000;0.125000;,
  0.375000;0.750000;,
  0.437500;0.750000;,
  0.500000;0.750000;,
  0.550000;0.750000;,
  0.590100;0.750000;,
  0.625000;0.750000;,
  0.875000;0.187500;,
  0.875000;0.125000;,
  0.590100;0.500000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.550000;0.500000;,
  0.437500;0.500000;,
  0.375000;0.500000;,
  0.125000;0.125000;,
  0.125000;0.187500;,
  0.404250;0.925000;,
  0.375000;0.925000;,
  0.375000;0.062500;,
  0.437500;0.062500;,
  0.500000;0.062500;,
  0.550000;0.062500;,
  0.590100;0.062500;,
  0.625000;0.062500;,
  0.700000;0.062500;,
  0.750000;0.062500;,
  0.800000;0.062500;,
  0.875000;0.062500;,
  0.625000;0.687500;,
  0.590100;0.687500;,
  0.550000;0.687500;,
  0.500000;0.687500;,
  0.437500;0.687500;,
  0.375000;0.687500;,
  0.125000;0.062500;,
  0.200000;0.062500;,
  0.250000;0.062500;,
  0.300000;0.062500;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  0.800000;0.250000;,
  0.700000;0.250000;,
  0.250000;0.250000;,
  0.300000;0.250000;,
  0.200000;0.250000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.550000;0.000000;,
  0.590100;0.000000;,
  0.625000;0.000000;,
  0.700000;0.000000;,
  0.750000;0.000000;,
  0.800000;0.000000;,
  0.875000;0.000000;,
  0.125000;0.000000;,
  0.200000;0.000000;,
  0.250000;0.000000;,
  0.300000;0.000000;;
 }
}
