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
 284;
 8041.20898;53.74525;-119.02280;,
 8046.54688;53.74525;142.35339;,
 8046.54688;-1209.05396;142.35339;,
 8041.20898;-1209.05396;-188.93045;,
 19.32350;66.46130;142.35339;,
 13.99535;66.46130;-119.02280;,
 17.17800;-1209.05396;-188.81551;,
 22.51050;-1209.05396;142.46815;,
 6874.32568;350.37982;-119.02280;,
 6874.32568;-1209.05396;-188.93045;,
 6805.65869;-1209.05396;-188.93045;,
 6805.65869;348.78986;-119.02280;,
 6810.99121;348.78986;142.35339;,
 6879.65771;350.37982;142.35339;,
 6879.65771;-1209.05396;142.35339;,
 6810.99121;-1209.05396;142.35339;,
 6945.97070;351.09796;-119.02280;,
 6945.97070;-1209.05396;-188.93045;,
 6951.30127;351.09796;142.35339;,
 6951.30127;-1209.05396;142.35339;,
 7014.46143;351.62897;-119.02280;,
 7014.46143;-1209.05396;-188.93045;,
 7019.79346;351.62897;142.35339;,
 7019.79346;-1209.05396;142.35339;,
 7101.09863;354.62567;-119.02280;,
 7101.09863;-1209.05396;-188.93045;,
 7106.43164;354.62567;142.35339;,
 7106.43164;-1209.05396;142.35339;,
 7186.43408;353.46326;-119.02280;,
 7186.43408;-1209.05396;-188.93045;,
 7191.76367;353.46326;142.35339;,
 7191.76367;-1209.05396;142.35339;,
 7268.03613;353.93549;-119.02280;,
 7268.03613;-1209.05396;-188.93045;,
 7273.37207;353.93549;142.35339;,
 7273.37207;-1209.05396;142.35339;,
 6298.25195;-1209.05396;-188.93045;,
 6298.25195;55.61035;-119.02280;,
 6303.58105;56.00025;142.35339;,
 6303.58105;-1209.05396;142.35339;,
 7401.16455;355.81061;-119.02280;,
 7401.16455;-1209.05396;-188.93045;,
 7406.49463;355.81061;142.35339;,
 7406.49463;-1209.05396;142.35339;,
 27277.26758;58.12560;-126.97870;,
 27277.26758;58.12560;148.39610;,
 27277.26758;-1206.25879;148.39610;,
 27277.26758;-1206.25879;-200.39005;,
 8041.75391;58.12561;152.69370;,
 8038.35205;58.12561;-126.97870;,
 8038.35205;-1206.25879;-200.39005;,
 8041.75391;-1206.25879;152.69370;,
 9712.86719;58.12560;-126.97870;,
 9949.93164;201.86505;-126.97870;,
 9946.86719;-1206.25879;-200.39005;,
 9709.29102;-1206.25879;-200.39005;,
 9471.71582;-1206.25879;-200.39005;,
 9475.80176;58.12560;-126.97870;,
 9483.62207;58.12560;148.39610;,
 9719.70898;58.12560;148.39610;,
 9955.79688;201.86505;148.39610;,
 9955.79688;-1206.25879;148.39610;,
 9719.70898;-1206.25879;148.39610;,
 9483.62207;-1206.25879;148.39610;,
 10186.99707;201.86505;-126.97870;,
 10424.06250;58.12560;-126.97870;,
 10422.01953;-1206.25879;-200.39005;,
 10184.44336;-1206.25879;-200.39005;,
 10191.88477;201.86505;148.39610;,
 10427.97266;58.12560;148.39610;,
 10427.97266;-1206.25879;148.39610;,
 10191.88477;-1206.25879;148.39610;,
 10661.12793;58.12560;-126.97870;,
 10898.19336;64.97430;-126.97870;,
 10897.17188;-1206.25879;-200.39005;,
 10659.59570;-1206.25879;-200.39005;,
 10664.06055;58.12560;148.39610;,
 10900.14844;64.97430;148.39610;,
 10900.14844;-1206.25879;148.39610;,
 10664.06055;-1206.25879;148.39610;,
 11135.25781;204.90915;-126.97870;,
 11134.74805;-1206.25879;-200.39005;,
 11136.23633;204.90915;148.39610;,
 11136.23633;-1206.25879;148.39610;,
 11361.09082;198.06044;-126.97870;,
 11358.18555;-1206.25879;-200.39005;,
 11365.98438;198.06044;148.39610;,
 11364.38379;-1206.25879;148.39610;,
 15563.29492;216.17802;148.39610;,
 15268.57910;216.17802;148.39610;,
 15268.14648;-1206.25879;148.39610;,
 15562.94922;-1206.25879;148.39610;,
 15562.23828;216.17802;-126.97870;,
 15267.25781;216.17802;-126.97870;,
 15266.47266;-1206.25879;-200.39005;,
 15561.60938;-1206.25879;-200.39005;,
 14982.26953;58.12560;-126.97870;,
 14981.33203;-1206.25879;-200.39005;,
 14983.84570;58.12560;148.39610;,
 14983.33008;-1206.25879;148.39610;,
 15926.13086;58.12560;148.39610;,
 15925.89258;-1206.25879;148.39610;,
 15925.39941;58.12560;-126.97870;,
 15924.96289;-1206.25879;-200.39005;,
 9269.17090;63.46886;-126.97870;,
 9264.40234;-1206.25879;-200.39005;,
 9057.08984;-1206.25879;-200.39005;,
 9062.54004;203.40370;-126.97870;,
 9075.63867;203.40370;150.54489;,
 9279.63086;63.46886;149.47049;,
 9279.63086;-1206.25879;149.47049;,
 9075.63867;-1206.25879;150.54489;,
 8802.41016;211.62045;-126.97870;,
 8798.49512;-1206.25879;-200.39005;,
 8812.45605;211.62045;151.61929;,
 8812.45605;-1206.25879;151.61929;,
 8488.25391;58.12561;-126.97870;,
 8486.29688;-1206.25879;-200.39005;,
 8494.97852;58.12561;152.15649;,
 8494.97852;-1206.25879;152.15649;,
 11564.64062;58.12560;-126.97870;,
 11563.75293;-1206.25879;-200.39005;,
 11569.24805;58.12560;148.39610;,
 11569.58984;-1206.25879;148.39610;,
 572.90381;222.28966;-80.78640;,
 824.51514;222.28966;-80.78640;,
 824.51514;198.63025;-105.38610;,
 572.90381;198.63025;-105.38610;,
 824.51514;222.28966;125.93905;,
 824.51514;198.63025;125.93905;,
 572.90381;222.28966;125.93905;,
 572.90381;198.63025;125.93905;,
 1123.01465;222.00584;-81.28730;,
 1374.62036;222.00584;-81.28730;,
 1374.62036;201.12000;-105.88700;,
 1123.01465;201.12000;-105.88700;,
 1374.62036;222.00584;120.62160;,
 1374.62036;201.12000;120.62160;,
 1123.01465;222.00584;120.62160;,
 1123.01465;201.12000;120.62160;,
 1734.94189;215.02576;-81.28730;,
 1986.54834;215.02576;-81.28730;,
 1986.54834;194.13976;-105.88700;,
 1734.94189;194.13976;-105.88700;,
 1986.54834;215.02576;120.62160;,
 1986.54834;194.13976;120.62160;,
 1734.94189;215.02576;120.62160;,
 1734.94189;194.13976;120.62160;,
 3188.53564;215.02576;-81.28730;,
 3440.14111;215.02576;-81.28730;,
 3440.14111;194.13976;-105.88700;,
 3188.53564;194.13976;-105.88700;,
 3440.14111;215.02576;120.62160;,
 3440.14111;194.13976;120.62160;,
 3188.53564;215.02576;120.62160;,
 3188.53564;194.13976;120.62160;,
 4738.65820;319.56824;-81.28731;,
 5677.43457;319.56824;-81.28731;,
 5677.43457;272.57501;-105.88701;,
 4738.65820;272.57501;-105.88701;,
 5677.43457;319.56824;120.62160;,
 5677.43457;272.57501;120.62160;,
 4738.65820;319.56824;120.62160;,
 4738.65820;272.57501;120.62160;,
 5764.22656;215.02576;-81.28730;,
 6015.83203;215.02576;-81.28730;,
 6015.83203;194.13976;-105.88700;,
 5764.22656;194.13976;-105.88700;,
 6015.83203;215.02576;120.62160;,
 6015.83203;194.13976;120.62160;,
 5764.22656;215.02576;120.62160;,
 5764.22656;194.13976;120.62160;,
 -279.47461;63.92300;-130.13530;,
 -91.06810;63.92300;-130.13530;,
 -91.06810;-1211.02417;-198.16824;,
 -279.47461;-1211.02417;-198.16824;,
 -88.19550;63.92300;149.53635;,
 -88.19550;-1211.02417;149.53635;,
 -276.60205;63.92300;149.53635;,
 -276.60205;-1211.02417;149.53635;,
 2135.83081;312.71320;-80.78640;,
 3074.61694;312.71320;-80.78640;,
 3074.61694;277.22400;-105.38610;,
 2135.83081;277.22400;-105.38610;,
 3074.61694;312.71320;125.93905;,
 3074.61694;277.22400;125.93905;,
 2135.83081;312.71320;125.93905;,
 2135.83081;277.22400;125.93905;,
 3509.55640;319.56824;-81.28731;,
 4448.32715;319.56824;-81.28731;,
 4448.32715;272.57501;-105.88701;,
 3509.55640;272.57501;-105.88701;,
 4448.32715;319.56824;120.62160;,
 4448.32715;272.57501;120.62160;,
 3509.55640;319.56824;120.62160;,
 3509.55640;272.57501;120.62160;,
 16721.58008;437.66858;-80.78640;,
 17660.36719;437.66858;-80.78640;,
 17660.36719;386.33716;-105.38610;,
 16721.58008;386.33716;-105.38610;,
 17660.36719;437.66858;125.93905;,
 17660.36719;386.33716;125.93905;,
 16721.58008;437.66858;125.93905;,
 16721.58008;386.33716;125.93905;,
 18030.97852;437.05280;-81.28730;,
 18969.75000;437.05280;-81.28730;,
 18969.75000;391.73889;-105.88700;,
 18030.97852;391.73889;-105.88700;,
 18969.75000;437.05280;120.62160;,
 18969.75000;391.73889;120.62160;,
 18030.97852;437.05280;120.62160;,
 18030.97852;391.73889;120.62160;,
 3188.53564;215.02576;-81.28730;,
 3440.14111;215.02576;-81.28730;,
 3440.14111;194.13976;-105.88700;,
 3188.53564;194.13976;-105.88700;,
 3440.14111;215.02576;120.62160;,
 3440.14111;194.13976;120.62160;,
 3188.53564;215.02576;120.62160;,
 3188.53564;194.13976;120.62160;,
 12928.20605;175.62384;-81.28730;,
 13179.81152;175.62384;-81.28730;,
 13179.81152;154.73784;-105.88700;,
 12928.20605;154.73784;-105.88700;,
 13179.81152;175.62384;120.62160;,
 13179.81152;154.73784;120.62160;,
 12928.20605;175.62384;120.62160;,
 12928.20605;154.73784;120.62160;,
 11885.85840;312.71320;-80.78640;,
 12824.64453;312.71320;-80.78640;,
 12824.64453;277.22400;-105.38610;,
 11885.85840;277.22400;-105.38610;,
 12824.64453;312.71320;125.93905;,
 12824.64453;277.22400;125.93905;,
 11885.85840;312.71320;125.93905;,
 11885.85840;277.22400;125.93905;,
 13274.18359;312.28754;-81.28730;,
 14212.95508;312.28754;-81.28730;,
 14212.95508;280.95868;-105.88700;,
 13274.18359;280.95868;-105.88700;,
 14212.95508;312.28754;120.62160;,
 14212.95508;280.95868;120.62160;,
 13274.18359;312.28754;120.62160;,
 13274.18359;280.95868;120.62160;,
 12928.20605;175.62384;-81.28730;,
 13179.81152;175.62384;-81.28730;,
 13179.81152;154.73784;-105.88700;,
 12928.20605;154.73784;-105.88700;,
 13179.81152;175.62384;120.62160;,
 13179.81152;154.73784;120.62160;,
 12928.20605;175.62384;120.62160;,
 12928.20605;154.73784;120.62160;,
 20316.01758;462.24091;-80.78640;,
 21254.80469;462.24091;-80.78640;,
 21254.80469;410.90948;-105.38610;,
 20316.01758;410.90948;-105.38610;,
 21254.80469;462.24091;125.93905;,
 21254.80469;410.90948;125.93905;,
 20316.01758;462.24091;125.93905;,
 20316.01758;410.90948;125.93905;,
 21625.41602;461.62512;-81.28730;,
 22564.18750;461.62512;-81.28730;,
 22564.18750;416.31122;-105.88700;,
 21625.41602;416.31122;-105.88700;,
 22564.18750;461.62512;120.62160;,
 22564.18750;416.31122;120.62160;,
 21625.41602;461.62512;120.62160;,
 21625.41602;416.31122;120.62160;,
 19584.77344;857.14905;-80.78640;,
 20523.56055;857.14905;-80.78640;,
 20523.56055;805.81763;-105.38610;,
 19584.77344;805.81763;-105.38610;,
 20523.56055;857.14905;125.93905;,
 20523.56055;805.81763;125.93905;,
 19584.77344;857.14905;125.93905;,
 19584.77344;805.81763;125.93905;,
 22320.94922;856.53333;-81.28730;,
 23259.72070;856.53333;-81.28730;,
 23259.72070;811.21936;-105.88700;,
 22320.94922;811.21936;-105.88700;,
 23259.72070;856.53333;120.62160;,
 23259.72070;811.21936;120.62160;,
 22320.94922;856.53333;120.62160;,
 22320.94922;811.21936;120.62160;;
 
 240;
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
 4;48,49,50,51;,
 4;41,40,0,3;,
 4;40,42,1,0;,
 4;43,41,3,2;,
 4;42,43,2,1;,
 4;37,36,6,5;,
 4;38,37,5,4;,
 4;36,39,7,6;,
 4;39,38,4,7;,
 4;52,53,54,55;,
 4;52,55,56,57;,
 4;52,57,58,59;,
 4;52,59,60,53;,
 4;55,54,61,62;,
 4;55,62,63,56;,
 4;59,58,63,62;,
 4;59,62,61,60;,
 4;64,65,66,67;,
 4;64,67,54,53;,
 4;64,53,60,68;,
 4;64,68,69,65;,
 4;67,66,70,71;,
 4;67,71,61,54;,
 4;68,60,61,71;,
 4;68,71,70,69;,
 4;72,73,74,75;,
 4;72,75,66,65;,
 4;72,65,69,76;,
 4;72,76,77,73;,
 4;75,74,78,79;,
 4;75,79,70,66;,
 4;76,69,70,79;,
 4;76,79,78,77;,
 4;80,81,74,73;,
 4;80,73,77,82;,
 4;81,83,78,74;,
 4;82,77,78,83;,
 4;84,85,81,80;,
 4;86,84,80,82;,
 4;85,87,83,81;,
 4;87,86,82,83;,
 4;88,89,90,91;,
 4;88,92,93,89;,
 4;91,90,94,95;,
 4;92,95,94,93;,
 4;96,93,94,97;,
 4;96,98,89,93;,
 4;97,94,90,99;,
 4;98,99,90,89;,
 4;100,88,91,101;,
 4;100,102,92,88;,
 4;101,91,95,103;,
 4;102,103,95,92;,
 4;46,45,100,101;,
 4;45,44,102,100;,
 4;47,46,101,103;,
 4;44,47,103,102;,
 4;104,57,56,105;,
 4;104,105,106,107;,
 4;104,107,108,109;,
 4;104,109,58,57;,
 4;105,56,63,110;,
 4;105,110,111,106;,
 4;109,108,111,110;,
 4;109,110,63,58;,
 4;112,107,106,113;,
 4;112,114,108,107;,
 4;113,106,111,115;,
 4;114,115,111,108;,
 4;116,112,113,117;,
 4;116,117,50,49;,
 4;116,49,48,118;,
 4;116,118,114,112;,
 4;117,113,115,119;,
 4;117,119,51,50;,
 4;118,48,51,119;,
 4;118,119,115,114;,
 4;120,96,97,121;,
 4;120,121,85,84;,
 4;122,98,96,120;,
 4;122,120,84,86;,
 4;121,97,99,123;,
 4;121,123,87,85;,
 4;123,99,98,122;,
 4;123,122,86,87;,
 4;124,125,126,127;,
 4;125,128,129,126;,
 4;128,130,131,129;,
 4;130,124,127,131;,
 4;130,128,125,124;,
 4;127,126,129,131;,
 4;132,133,134,135;,
 4;133,136,137,134;,
 4;136,138,139,137;,
 4;138,132,135,139;,
 4;138,136,133,132;,
 4;135,134,137,139;,
 4;140,141,142,143;,
 4;141,144,145,142;,
 4;144,146,147,145;,
 4;146,140,143,147;,
 4;146,144,141,140;,
 4;143,142,145,147;,
 4;148,149,150,151;,
 4;149,152,153,150;,
 4;152,154,155,153;,
 4;154,148,151,155;,
 4;154,152,149,148;,
 4;151,150,153,155;,
 4;156,157,158,159;,
 4;157,160,161,158;,
 4;160,162,163,161;,
 4;162,156,159,163;,
 4;162,160,157,156;,
 4;159,158,161,163;,
 4;164,165,166,167;,
 4;165,168,169,166;,
 4;168,170,171,169;,
 4;170,164,167,171;,
 4;170,168,165,164;,
 4;167,166,169,171;,
 4;172,173,174,175;,
 4;173,176,177,174;,
 4;176,178,179,177;,
 4;178,172,175,179;,
 4;178,176,173,172;,
 4;175,174,177,179;,
 4;180,181,182,183;,
 4;181,184,185,182;,
 4;184,186,187,185;,
 4;186,180,183,187;,
 4;186,184,181,180;,
 4;183,182,185,187;,
 4;188,189,190,191;,
 4;189,192,193,190;,
 4;192,194,195,193;,
 4;194,188,191,195;,
 4;194,192,189,188;,
 4;191,190,193,195;,
 4;196,197,198,199;,
 4;197,200,201,198;,
 4;200,202,203,201;,
 4;202,196,199,203;,
 4;202,200,197,196;,
 4;199,198,201,203;,
 4;204,205,206,207;,
 4;205,208,209,206;,
 4;208,210,211,209;,
 4;210,204,207,211;,
 4;210,208,205,204;,
 4;207,206,209,211;,
 4;212,213,214,215;,
 4;213,216,217,214;,
 4;216,218,219,217;,
 4;218,212,215,219;,
 4;218,216,213,212;,
 4;215,214,217,219;,
 4;220,221,222,223;,
 4;221,224,225,222;,
 4;224,226,227,225;,
 4;226,220,223,227;,
 4;226,224,221,220;,
 4;223,222,225,227;,
 4;228,229,230,231;,
 4;229,232,233,230;,
 4;232,234,235,233;,
 4;234,228,231,235;,
 4;234,232,229,228;,
 4;231,230,233,235;,
 4;236,237,238,239;,
 4;237,240,241,238;,
 4;240,242,243,241;,
 4;242,236,239,243;,
 4;242,240,237,236;,
 4;239,238,241,243;,
 4;244,245,246,247;,
 4;245,248,249,246;,
 4;248,250,251,249;,
 4;250,244,247,251;,
 4;250,248,245,244;,
 4;247,246,249,251;,
 4;252,253,254,255;,
 4;253,256,257,254;,
 4;256,258,259,257;,
 4;258,252,255,259;,
 4;258,256,253,252;,
 4;255,254,257,259;,
 4;260,261,262,263;,
 4;261,264,265,262;,
 4;264,266,267,265;,
 4;266,260,263,267;,
 4;266,264,261,260;,
 4;263,262,265,267;,
 4;268,269,270,271;,
 4;269,272,273,270;,
 4;272,274,275,273;,
 4;274,268,271,275;,
 4;274,272,269,268;,
 4;271,270,273,275;,
 4;276,277,278,279;,
 4;277,280,281,278;,
 4;280,282,283,281;,
 4;282,276,279,283;,
 4;282,280,277,276;,
 4;279,278,281,283;;
 
 MeshMaterialList {
  4;
  240;
  2,
  0,
  1,
  0,
  0,
  2,
  1,
  0,
  0,
  2,
  1,
  0,
  0,
  2,
  1,
  0,
  0,
  2,
  1,
  0,
  0,
  2,
  1,
  0,
  0,
  2,
  1,
  2,
  0,
  2,
  1,
  0,
  0,
  2,
  0,
  0,
  1,
  0,
  0,
  2,
  1,
  2,
  0,
  2,
  1,
  1,
  0,
  0,
  0,
  0,
  2,
  2,
  1,
  1,
  0,
  0,
  0,
  0,
  2,
  2,
  1,
  1,
  0,
  0,
  0,
  0,
  2,
  2,
  1,
  0,
  0,
  2,
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
  2,
  0,
  0,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  2,
  2,
  1,
  0,
  0,
  2,
  1,
  1,
  0,
  0,
  0,
  0,
  2,
  2,
  1,
  1,
  0,
  0,
  0,
  0,
  2,
  2,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0,
  1,
  0,
  2,
  0,
  0,
  0;;
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game305\\Desktop\\SchoolFestival-TeamA\\���Ő���\\��METALSLUG\\data\\materialtexture\\OIP.jpg";
   }
  }
  Material {
   0.480000;0.480000;0.480000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game305\\Desktop\\SchoolFestival-TeamA\\���Ő���\\��METALSLUG\\data\\materialtexture\\OIP.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game305\\Desktop\\SchoolFestival-TeamA\\���Ő���\\��METALSLUG\\data\\materialtexture\\OIP.jpg";
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
  161;
  -0.999829;-0.002936;0.018238;,
  0.999833;0.000446;-0.018264;,
  -0.006455;0.052463;-0.998602;,
  -0.258014;0.966130;0.004542;,
  0.000000;-1.000000;-0.000000;,
  -0.006733;0.047409;-0.998853;,
  -0.269996;0.962848;0.005173;,
  -0.000371;0.044790;-0.998996;,
  -0.016586;0.999862;0.000338;,
  -0.000199;0.044765;-0.998998;,
  -0.008888;0.999961;0.000181;,
  -0.000473;0.044731;-0.998999;,
  -0.021162;0.999776;0.000432;,
  -0.000234;0.044692;-0.999001;,
  -0.010477;0.999945;0.000214;,
  0.000087;0.044684;-0.999001;,
  0.003917;0.999992;-0.000080;,
  -0.000222;0.044672;-0.999002;,
  -0.009935;0.999951;0.000203;,
  0.005108;0.047304;-0.998868;,
  0.211810;0.977301;-0.004322;,
  -0.999941;-0.000280;0.010899;,
  1.000000;0.000000;0.000000;,
  0.000373;0.057901;-0.998322;,
  0.013009;0.999915;-0.000431;,
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
  -0.249383;0.968404;0.001243;,
  0.009351;0.053560;-0.998521;,
  0.311068;0.950373;-0.005264;,
  -0.250576;0.968096;0.001318;,
  0.000000;0.000000;1.000000;,
  0.203887;0.978994;-0.000662;,
  -0.007146;0.056361;-0.998385;,
  -0.250576;0.968096;0.001318;,
  0.009189;0.053323;-0.998535;,
  0.309565;0.950788;-0.013142;,
  0.009152;0.056316;-0.998371;,
  0.307009;0.951619;-0.012920;,
  -0.005912;0.053361;-0.998558;,
  -0.208940;0.977910;0.006091;,
  -0.006323;0.056416;-0.998387;,
  -0.224262;0.974506;0.006739;,
  0.008956;0.056504;-0.998362;,
  0.296749;0.954942;-0.005119;,
  0.000005;0.000022;1.000000;,
  0.010530;0.049950;-0.998696;,
  0.426783;0.904312;-0.008709;,
  0.000039;0.054914;-0.998491;,
  0.001696;0.999998;-0.000780;,
  0.000009;0.000045;1.000000;,
  0.002633;0.000000;0.999997;,
  0.005606;0.053144;-0.998571;,
  -0.007146;0.053150;-0.998561;,
  0.005606;0.056355;-0.998395;,
  0.000000;1.000000;0.000000;,
  0.000000;0.057963;-0.998319;,
  0.005267;0.000000;0.999986;,
  0.004675;0.000000;0.999989;,
  0.002887;0.000000;0.999996;,
  0.000000;0.057963;-0.998319;,
  0.001439;0.000000;0.999999;,
  0.001185;0.000000;0.999999;,
  0.000000;0.927563;-0.373666;,
  0.000000;0.720747;-0.693198;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.938697;-0.344743;,
  0.000000;0.762305;-0.647218;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.938697;-0.344745;,
  0.000000;0.762302;-0.647221;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.938697;-0.344745;,
  0.000000;0.762302;-0.647221;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.463773;-0.885954;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.938697;-0.344745;,
  0.000000;0.762302;-0.647221;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.053286;-0.998579;,
  0.999957;0.000220;-0.009266;,
  0.000000;0.000000;1.000000;,
  -0.999957;-0.000220;0.009266;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.885913;-0.463852;,
  0.000000;0.569684;-0.821864;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.463773;-0.885954;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.432169;-0.901793;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.477103;-0.878848;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.938697;-0.344745;,
  0.000000;0.762302;-0.647221;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.938697;-0.344745;,
  0.000000;0.762302;-0.647221;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.885913;-0.463852;,
  0.000000;0.569684;-0.821864;,
  0.000000;0.899326;-0.437278;,
  0.000000;0.617576;-0.786511;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.432169;-0.901793;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.477103;-0.878848;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.432169;-0.901793;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.477102;-0.878848;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  240;
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;7,7,5,5;,
  4;8,6,6,8;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;9,9,7,7;,
  4;10,8,8,10;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;11,11,9,9;,
  4;12,10,10,12;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;13,13,11,11;,
  4;14,12,12,14;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;15,15,13,13;,
  4;16,14,14,16;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;17,17,15,15;,
  4;18,16,16,18;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;2,2,5,5;,
  4;3,3,6,6;,
  4;4,4,4,4;,
  4;54,54,40,40;,
  4;19,19,17,17;,
  4;20,18,18,20;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;22,22,22,22;,
  4;21,21,21,21;,
  4;19,19,55,55;,
  4;20,20,56,56;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;2,2,57,57;,
  4;3,3,58,58;,
  4;4,4,4,4;,
  4;54,54,59,59;,
  4;29,27,27,29;,
  4;29,29,23,23;,
  4;28,24,24,28;,
  4;28,28,28,28;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;40,60,60,40;,
  4;40,40,40,40;,
  4;30,25,25,30;,
  4;30,30,27,27;,
  4;26,28,28,26;,
  4;26,26,26,26;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;33,31,31,33;,
  4;33,33,25,25;,
  4;34,26,26,34;,
  4;34,34,32,32;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;35,35,31,31;,
  4;36,32,32,36;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;37,37,35,35;,
  4;38,38,36,36;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;41,41,39,39;,
  4;4,4,4,4;,
  4;61,61,62,62;,
  4;42,62,62,42;,
  4;43,43,39,39;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;4,4,4,4;,
  4;63,63,61,61;,
  4;40,40,40,40;,
  4;64,64,41,41;,
  4;4,4,4,4;,
  4;65,65,63,63;,
  4;46,23,23,46;,
  4;46,46,44,44;,
  4;47,45,45,47;,
  4;47,47,24,24;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;66,67,67,66;,
  4;66,66,60,60;,
  4;48,44,44,48;,
  4;49,49,45,45;,
  4;4,4,4,4;,
  4;68,68,67,67;,
  4;50,48,48,50;,
  4;50,50,69,69;,
  4;51,64,64,51;,
  4;51,51,49,49;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;70,71,71,70;,
  4;70,70,68,68;,
  4;52,42,42,52;,
  4;52,52,37,37;,
  4;53,43,43,53;,
  4;53,53,38,38;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;40,40,40,40;,
  4;40,40,40,40;,
  4;72,72,73,73;,
  4;74,74,74,74;,
  4;75,75,75,75;,
  4;78,78,78,78;,
  4;79,79,72,72;,
  4;80,80,80,80;,
  4;76,76,77,77;,
  4;74,74,74,74;,
  4;75,75,75,75;,
  4;78,78,78,78;,
  4;79,79,76,76;,
  4;80,80,80,80;,
  4;81,81,82,82;,
  4;83,83,83,83;,
  4;84,84,84,84;,
  4;85,85,85,85;,
  4;86,86,81,81;,
  4;87,87,87,87;,
  4;88,88,89,89;,
  4;90,90,90,90;,
  4;91,91,91,91;,
  4;92,92,92,92;,
  4;93,93,88,88;,
  4;94,94,94,94;,
  4;95,95,95,95;,
  4;96,96,96,96;,
  4;97,97,97,97;,
  4;98,98,98,98;,
  4;99,99,99,99;,
  4;100,100,100,100;,
  4;101,101,102,102;,
  4;103,103,103,103;,
  4;104,104,104,104;,
  4;105,105,105,105;,
  4;106,106,101,101;,
  4;107,107,107,107;,
  4;108,108,108,108;,
  4;109,109,109,109;,
  4;110,110,110,110;,
  4;111,111,111,111;,
  4;112,112,112,112;,
  4;113,113,113,113;,
  4;114,114,115,115;,
  4;116,116,116,116;,
  4;117,117,117,117;,
  4;119,119,119,119;,
  4;120,120,114,114;,
  4;121,121,121,121;,
  4;118,118,118,118;,
  4;116,116,116,116;,
  4;117,117,117,117;,
  4;119,119,119,119;,
  4;120,120,120,120;,
  4;121,121,121,121;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;126,126,126,126;,
  4;127,127,127,127;,
  4;128,128,128,128;,
  4;125,125,125,125;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;126,126,126,126;,
  4;127,127,127,127;,
  4;128,128,128,128;,
  4;129,129,130,130;,
  4;131,131,131,131;,
  4;132,132,132,132;,
  4;133,133,133,133;,
  4;134,134,129,129;,
  4;135,135,135,135;,
  4;136,136,137,137;,
  4;138,138,138,138;,
  4;139,139,139,139;,
  4;144,144,144,144;,
  4;145,145,136,136;,
  4;146,146,146,146;,
  4;140,140,141,141;,
  4;138,138,138,138;,
  4;139,139,139,139;,
  4;144,144,144,144;,
  4;145,145,140,140;,
  4;146,146,146,146;,
  4;142,142,143,143;,
  4;138,138,138,138;,
  4;139,139,139,139;,
  4;144,144,144,144;,
  4;145,145,142,142;,
  4;146,146,146,146;,
  4;136,136,137,137;,
  4;138,138,138,138;,
  4;139,139,139,139;,
  4;144,144,144,144;,
  4;145,145,136,136;,
  4;146,146,146,146;,
  4;147,147,147,147;,
  4;148,148,148,148;,
  4;149,149,149,149;,
  4;151,151,151,151;,
  4;152,152,152,152;,
  4;153,153,153,153;,
  4;150,150,150,150;,
  4;148,148,148,148;,
  4;149,149,149,149;,
  4;151,151,151,151;,
  4;152,152,152,152;,
  4;153,153,153,153;,
  4;154,154,154,154;,
  4;155,155,155,155;,
  4;156,156,156,156;,
  4;158,158,158,158;,
  4;159,159,159,159;,
  4;160,160,160,160;,
  4;157,157,157,157;,
  4;155,155,155,155;,
  4;156,156,156,156;,
  4;158,158,158,158;,
  4;159,159,159,159;,
  4;160,160,160,160;;
 }
 MeshTextureCoords {
  284;
  80.912086;-0.037453;,
  80.965469;-0.037453;,
  80.965469;12.590539;,
  80.912086;12.590539;,
  0.693235;-0.164613;,
  0.639953;-0.164613;,
  0.671780;12.590539;,
  0.725105;12.590539;,
  69.243256;-3.003798;,
  69.243256;12.590539;,
  68.556587;12.590539;,
  68.556587;-2.987899;,
  68.609909;-2.987899;,
  69.296577;-3.003798;,
  69.296577;12.590539;,
  68.609909;12.590539;,
  69.959709;-3.010980;,
  69.959709;12.590539;,
  70.013008;-3.010980;,
  70.013008;12.590539;,
  70.644615;-3.016290;,
  70.644615;12.590539;,
  70.697929;-3.016290;,
  70.697929;12.590539;,
  71.510986;-3.046257;,
  71.510986;12.590539;,
  71.564316;-3.046257;,
  71.564316;12.590539;,
  72.364342;-3.034632;,
  72.364342;12.590539;,
  72.417633;-3.034632;,
  72.417633;12.590539;,
  73.180359;-3.039355;,
  73.180359;12.590539;,
  73.233719;-3.039355;,
  73.233719;12.590539;,
  63.482517;12.590539;,
  63.482517;-0.056104;,
  63.535809;-0.060003;,
  63.535809;12.590539;,
  74.511642;-3.058106;,
  74.511642;12.590539;,
  74.564941;-3.058106;,
  74.564941;12.590539;,
  273.272675;-0.081256;,
  273.272675;-0.081256;,
  273.272675;12.562588;,
  273.272675;12.562588;,
  80.917534;-0.081256;,
  80.883522;-0.081256;,
  80.883522;12.562588;,
  80.917534;12.562588;,
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
  114.110909;-1.480604;,
  114.081856;12.562588;,
  114.159843;-1.480604;,
  114.143837;12.562588;,
  156.132950;-1.661780;,
  153.185791;-1.661780;,
  153.181458;12.562588;,
  156.129486;12.562588;,
  156.122375;-1.661780;,
  153.172577;-1.661780;,
  153.164719;12.562588;,
  156.116089;12.562588;,
  150.322693;-0.081256;,
  150.313324;12.562588;,
  150.338455;-0.081256;,
  150.333298;12.562588;,
  159.761307;-0.081256;,
  159.758926;12.562588;,
  159.753998;-0.081256;,
  159.749619;12.562588;,
  93.191704;-0.134689;,
  93.144020;12.562588;,
  91.070900;12.562588;,
  91.125397;-1.534037;,
  91.256386;-1.534037;,
  93.296303;-0.134689;,
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
  116.137527;12.562588;,
  116.192474;-0.081256;,
  116.195892;12.562588;,
  6.229038;-1.722897;,
  8.745152;-1.722897;,
  8.745152;-1.486302;,
  6.229038;-1.486302;,
  8.745152;-1.722897;,
  8.745152;-1.486302;,
  6.229038;-1.722897;,
  6.229038;-1.486302;,
  11.730146;-1.720058;,
  14.246203;-1.720058;,
  14.246203;-1.511200;,
  11.730146;-1.511200;,
  14.246203;-1.720058;,
  14.246203;-1.511200;,
  11.730146;-1.720058;,
  11.730146;-1.511200;,
  17.849419;-1.650258;,
  20.365482;-1.650258;,
  20.365482;-1.441398;,
  17.849419;-1.441398;,
  20.365482;-1.650258;,
  20.365482;-1.441398;,
  17.849419;-1.650258;,
  17.849419;-1.441398;,
  32.385353;-1.650258;,
  34.901409;-1.650258;,
  34.901409;-1.441398;,
  32.385353;-1.441398;,
  34.901409;-1.650258;,
  34.901409;-1.441398;,
  32.385353;-1.650258;,
  32.385353;-1.441398;,
  47.886581;-2.695682;,
  57.274345;-2.695682;,
  57.274345;-2.225750;,
  47.886581;-2.225750;,
  57.274345;-2.695682;,
  57.274345;-2.225750;,
  47.886581;-2.695682;,
  47.886581;-2.225750;,
  58.142265;-1.650258;,
  60.658318;-1.650258;,
  60.658318;-1.441398;,
  58.142265;-1.441398;,
  60.658318;-1.650258;,
  60.658318;-1.441398;,
  58.142265;-1.650258;,
  58.142265;-1.441398;,
  -2.294746;-0.139230;,
  -0.410681;-0.139230;,
  -0.410681;12.610242;,
  -2.294746;12.610242;,
  -0.381955;-0.139230;,
  -0.381955;12.610242;,
  -2.266021;-0.139230;,
  -2.266021;12.610242;,
  21.858307;-2.627132;,
  31.246168;-2.627132;,
  31.246168;-2.272240;,
  21.858307;-2.272240;,
  31.246168;-2.627132;,
  31.246168;-2.272240;,
  21.858307;-2.627132;,
  21.858307;-2.272240;,
  35.595562;-2.695682;,
  44.983269;-2.695682;,
  44.983269;-2.225750;,
  35.595562;-2.225750;,
  44.983269;-2.695682;,
  44.983269;-2.225750;,
  35.595562;-2.695682;,
  35.595562;-2.225750;,
  167.715790;-3.876686;,
  177.103668;-3.876686;,
  177.103668;-3.363372;,
  167.715790;-3.363372;,
  177.103668;-3.876686;,
  177.103668;-3.363372;,
  167.715790;-3.876686;,
  167.715790;-3.363372;,
  180.809784;-3.870528;,
  190.197495;-3.870528;,
  190.197495;-3.417389;,
  180.809784;-3.417389;,
  190.197495;-3.870528;,
  190.197495;-3.417389;,
  180.809784;-3.870528;,
  180.809784;-3.417389;,
  32.385353;-1.650258;,
  34.901409;-1.650258;,
  34.901409;-1.441398;,
  32.385353;-1.441398;,
  34.901409;-1.650258;,
  34.901409;-1.441398;,
  32.385353;-1.650258;,
  32.385353;-1.441398;,
  129.782059;-1.256238;,
  132.298111;-1.256238;,
  132.298111;-1.047378;,
  129.782059;-1.047378;,
  132.298111;-1.256238;,
  132.298111;-1.047378;,
  129.782059;-1.256238;,
  129.782059;-1.047378;,
  119.358582;-2.627132;,
  128.746445;-2.627132;,
  128.746445;-2.272240;,
  119.358582;-2.272240;,
  128.746445;-2.627132;,
  128.746445;-2.272240;,
  119.358582;-2.627132;,
  119.358582;-2.272240;,
  133.241837;-2.622875;,
  142.629547;-2.622875;,
  142.629547;-2.309587;,
  133.241837;-2.309587;,
  142.629547;-2.622875;,
  142.629547;-2.309587;,
  133.241837;-2.622875;,
  133.241837;-2.309587;,
  129.782059;-1.256238;,
  132.298111;-1.256238;,
  132.298111;-1.047378;,
  129.782059;-1.047378;,
  132.298111;-1.256238;,
  132.298111;-1.047378;,
  129.782059;-1.256238;,
  129.782059;-1.047378;,
  203.660172;-4.122409;,
  213.048035;-4.122409;,
  213.048035;-3.609095;,
  203.660172;-3.609095;,
  213.048035;-4.122409;,
  213.048035;-3.609095;,
  203.660172;-4.122409;,
  203.660172;-3.609095;,
  216.754150;-4.116251;,
  226.141876;-4.116251;,
  226.141876;-3.663112;,
  216.754150;-3.663112;,
  226.141876;-4.116251;,
  226.141876;-3.663112;,
  216.754150;-4.116251;,
  216.754150;-3.663112;,
  196.347733;-8.071490;,
  205.735596;-8.071490;,
  205.735596;-7.558176;,
  196.347733;-7.558176;,
  205.735596;-8.071490;,
  205.735596;-7.558176;,
  196.347733;-8.071490;,
  196.347733;-7.558176;,
  223.709488;-8.065333;,
  233.097198;-8.065333;,
  233.097198;-7.612193;,
  223.709488;-7.612193;,
  233.097198;-8.065333;,
  233.097198;-7.612193;,
  223.709488;-8.065333;,
  223.709488;-7.612193;;
 }
}
