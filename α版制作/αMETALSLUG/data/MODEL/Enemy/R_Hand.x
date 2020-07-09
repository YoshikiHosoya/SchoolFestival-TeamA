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
 2.12481;-6.90926;-1.67205;,
 1.96875;-6.65555;-1.49373;,
 1.94465;-6.94058;-1.64581;,
 2.28625;-6.65462;-1.67436;,
 2.03647;-6.45216;-1.45473;,
 1.82204;-6.95566;-1.64477;,
 1.66956;-6.60135;-1.40810;,
 1.48714;-6.80809;-1.58688;,
 1.73676;-6.27107;-1.33934;,
 1.44555;-6.45309;-1.56324;,
 1.49986;-6.36537;-1.46097;,
 1.51580;-6.15505;-1.49050;,
 2.12684;-6.16695;-1.58197;,
 2.36322;-6.48654;-1.66604;,
 1.88277;-6.01256;-1.44601;,
 1.67962;-6.03198;-1.39314;,
 0.28750;-3.19250;-2.41644;,
 0.90124;-5.51402;-2.93895;,
 0.70461;-5.50172;-2.63757;,
 0.18666;-3.55253;-2.33665;,
 0.66209;-5.50189;-2.39315;,
 0.37873;-5.18363;-2.36981;,
 0.70178;-5.47398;-2.14689;,
 0.59905;-5.35143;-2.20629;,
 1.20806;-5.07073;-1.86492;,
 0.82122;-5.19912;-2.02185;,
 1.59445;-5.03329;-1.90178;,
 1.23915;-5.09026;-2.08472;,
 1.76923;-5.06749;-1.98383;,
 1.29878;-4.86769;-2.05901;,
 1.91704;-5.11620;-2.19809;,
 1.40053;-4.88184;-2.11193;,
 1.99163;-5.23841;-2.57083;,
 1.32149;-3.70091;-1.94604;,
 1.79281;-5.26649;-2.80045;,
 1.21893;-3.37589;-2.07530;,
 1.44184;-5.33976;-3.06896;,
 0.91222;-3.07821;-2.10812;,
 1.05645;-5.38090;-3.11629;,
 0.57322;-2.94069;-2.30556;,
 0.30621;-2.21137;-1.15832;,
 0.47159;-2.15983;-1.22910;,
 0.11652;-2.37888;-1.52476;,
 0.02170;-2.96998;-1.70799;,
 -0.07318;-4.25064;-1.89115;,
 0.27039;-4.50794;-1.89115;,
 0.64227;-4.54145;-1.89115;,
 1.00594;-4.55613;-1.89115;,
 1.27781;-3.39987;-1.70943;,
 1.21014;-2.92982;-1.52684;,
 1.02154;-2.21137;-1.15832;,
 0.70259;-2.15983;-1.22910;,
 0.98745;-5.82795;-1.81014;,
 1.01386;-5.74527;-1.62501;,
 1.05766;-6.10582;-2.04520;,
 1.25972;-6.31782;-2.22981;,
 1.40712;-6.33417;-2.42014;,
 1.72728;-6.27414;-2.47983;,
 2.01318;-5.96085;-2.53628;,
 2.19392;-5.71614;-2.36010;,
 2.09957;-5.43047;-2.05987;,
 2.25598;-6.18377;-1.67956;,
 1.62536;-5.29769;-1.78432;,
 1.49390;-5.23598;-1.73901;,
 1.25232;-5.40956;-1.73329;,
 2.16260;-6.13223;1.82660;,
 2.15012;-6.13985;-1.63946;,
 2.25506;-6.00713;-1.64050;,
 2.26020;-6.00886;1.82735;,
 2.26020;-6.00886;1.82735;,
 2.25506;-6.00713;-1.64050;,
 2.24870;-5.83812;-1.63946;,
 2.25430;-5.85170;1.82660;,
 2.06738;-5.94588;2.06061;,
 -0.74621;-7.39180;2.06061;,
 -0.00211;-7.30264;1.98983;,
 2.13117;-6.07918;1.99231;,
 2.13117;-6.07918;1.99231;,
 -0.00211;-7.30264;1.98983;,
 0.03031;-7.35464;1.81880;,
 -0.91967;-7.78089;1.81880;,
 -0.91967;-7.78089;-1.64940;,
 -0.78602;-7.86595;-1.64974;,
 -0.78602;-7.86595;1.81897;,
 0.03031;-7.35464;-1.64940;,
 -1.90264;-5.70505;2.06061;,
 -2.26152;-5.83587;1.98862;,
 -0.86986;-7.74524;1.98983;,
 -0.86986;-7.74524;1.98983;,
 -2.26152;-5.83587;1.98862;,
 -2.31092;-5.88151;1.80557;,
 1.35165;-1.09758;1.03719;,
 1.35165;-1.09758;-0.86034;,
 1.03766;-0.26328;-0.71034;,
 1.03766;-0.26328;0.87881;,
 1.03766;-0.26328;-0.71034;,
 0.62615;0.02169;-0.43686;,
 0.62615;0.02169;0.60626;,
 0.82139;-1.09758;1.58010;,
 0.78545;-1.98164;1.64320;,
 1.27890;-1.98164;1.25318;,
 1.29318;-1.09758;1.20759;,
 1.34038;-1.98164;1.07319;,
 -0.49648;0.02169;0.60626;,
 -0.78984;-0.26328;1.02136;,
 0.91944;-0.26328;1.02136;,
 -0.55981;-1.09758;1.58010;,
 -1.27421;-1.09758;0.78862;,
 -1.22614;-1.98164;0.81849;,
 -0.97190;-1.98164;1.25485;,
 -1.03159;-1.09758;1.20759;,
 -0.65503;-1.98164;1.64320;,
 -0.49648;0.02169;-0.43686;,
 -0.90800;-0.26328;-0.70941;,
 -0.90800;-0.26328;0.87876;,
 -0.90800;-0.26328;0.87876;,
 -0.90800;-0.26328;-0.70941;,
 -1.27421;-1.09758;-0.61101;,
 1.34038;-1.98164;-0.78395;,
 1.29479;-2.05190;-0.89726;,
 1.29318;-1.09758;-1.03068;,
 1.29318;-1.09758;-1.03068;,
 1.29479;-2.05190;-0.89726;,
 1.12422;-2.22166;-0.93615;,
 1.09412;-1.09758;-1.22413;,
 -0.33966;-1.09758;-1.23719;,
 -0.78978;-0.26328;-0.85190;,
 0.91904;-0.26328;-0.85190;,
 -0.00211;-7.30264;-1.82043;,
 2.12557;-6.08323;-1.81742;,
 -0.74621;-7.39180;-1.89115;,
 2.06738;-5.94588;-1.89115;,
 -2.31092;-5.88151;-1.63611;,
 -2.26140;-5.83587;-1.81922;,
 -0.86986;-7.74524;-1.82043;,
 -1.90264;-5.70505;-1.89115;,
 -2.12845;-4.91079;1.80221;,
 -2.12897;-4.91293;-1.63611;,
 -2.37275;-5.74145;-1.63617;,
 -2.37258;-5.74088;1.80360;,
 -2.37258;-5.74088;1.80360;,
 -2.37275;-5.74145;-1.63617;,
 -1.38827;-3.12148;2.06061;,
 -1.53180;-3.07982;1.98636;,
 -2.06552;-4.93460;1.98746;,
 -1.59126;-3.06255;1.80712;,
 -1.59126;-3.06255;-1.62056;,
 -1.53856;-3.09947;-1.81194;,
 -2.06570;-4.93587;-1.81916;,
 -2.06570;-4.93587;-1.81916;,
 -1.53856;-3.09947;-1.81194;,
 -1.41139;-3.18868;-1.89115;,
 -0.43003;-2.04814;-1.30028;,
 -1.22614;-1.98164;-0.64360;,
 1.28185;-3.94798;2.06061;,
 -1.35303;-2.60064;-1.31138;,
 -1.49251;-2.87106;-1.49420;,
 1.22384;-2.93416;-1.52667;,
 1.49546;-4.00998;-1.58930;,
 1.46120;-3.56183;-1.46941;,
 1.49546;-4.00998;1.79609;,
 1.42237;-3.05388;-1.28965;,
 1.32830;-4.19650;-1.89115;,
 -1.11526;-2.53668;-1.52476;,
 -1.25486;-2.81357;-1.70799;,
 1.43294;-3.99184;1.98313;,
 2.19797;-5.87649;1.99220;,
 1.36367;-2.99477;-1.45797;,
 1.36367;-2.99477;-1.45797;,
 -0.97363;-2.00111;-1.08360;,
 -1.03159;-1.09758;-1.03068;,
 -1.03159;-1.09758;-1.03068;,
 -0.97363;-2.00111;-1.08360;,
 -1.26815;-2.54847;-1.46438;,
 -1.26815;-2.54847;-1.46438;,
 1.40729;-3.49042;-1.64073;,
 1.40729;-3.49042;-1.64073;,
 -1.40746;-2.82068;-1.64732;,
 -1.40746;-2.82068;-1.64732;,
 1.44652;-4.06464;-1.80275;,
 2.19525;-5.86897;-1.81742;,
 2.19525;-5.86897;-1.81742;,
 1.44652;-4.06464;-1.80275;,
 2.22339;-5.99702;1.96215;,
 2.22339;-5.99702;1.96215;,
 -0.77863;-7.82828;1.95845;,
 -0.77863;-7.82828;1.95845;,
 1.26723;-0.98231;1.17627;,
 -1.00565;-0.98231;1.17621;,
 1.26700;-0.98231;-0.99982;,
 1.26700;-0.98231;-0.99982;,
 -1.00565;-0.98231;-0.99942;,
 -1.00565;-0.98231;-0.99942;,
 2.22004;-5.99563;-1.78512;,
 2.22004;-5.99563;-1.78512;,
 -0.77863;-7.82828;-1.78911;,
 -2.33103;-5.73255;1.95476;,
 -2.33103;-5.73255;1.95476;,
 -2.33103;-5.73302;-1.78628;,
 -2.33103;-5.73302;-1.78628;;
 
 188;
 3;0,1,2;,
 4;1,0,3,4;,
 4;5,1,6,7;,
 4;6,1,4,8;,
 3;7,6,9;,
 4;10,6,8,11;,
 3;12,4,13;,
 4;14,8,4,12;,
 3;11,8,15;,
 3;2,1,5;,
 3;4,3,13;,
 3;15,8,14;,
 3;9,6,10;,
 4;16,17,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 4;25,24,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;31,30,32,33;,
 4;34,35,33,32;,
 4;36,37,35,34;,
 4;37,36,38,39;,
 4;39,38,17,16;,
 4;40,41,37,39;,
 4;40,39,16,42;,
 4;42,16,19,43;,
 4;44,43,19,21;,
 4;45,44,21,23;,
 4;46,45,23,25;,
 4;47,46,25,27;,
 4;47,27,29,48;,
 4;48,29,31,49;,
 4;49,31,33,50;,
 4;35,51,50,33;,
 4;37,41,51,35;,
 4;20,52,53,22;,
 4;18,54,52,20;,
 4;17,55,54,18;,
 4;38,56,55,17;,
 4;36,57,56,38;,
 4;57,36,34,58;,
 4;58,34,32,59;,
 3;60,61,59;,
 3;62,61,60;,
 4;26,63,62,28;,
 4;24,64,63,26;,
 4;22,53,64,24;,
 4;52,9,10,53;,
 4;54,7,9,52;,
 4;55,5,7,54;,
 4;56,2,5,55;,
 4;57,0,2,56;,
 4;0,57,58,3;,
 4;3,58,59,13;,
 4;61,12,13,59;,
 4;62,14,12,61;,
 4;63,15,14,62;,
 4;64,11,15,63;,
 4;53,10,11,64;,
 4;65,66,67,68;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;77,78,79,65;,
 4;80,81,82,83;,
 4;83,82,84,79;,
 4;74,85,86,87;,
 4;88,89,90,80;,
 4;91,92,93,94;,
 4;94,95,96,97;,
 4;98,99,100,101;,
 4;101,100,102,91;,
 4;97,103,104,105;,
 4;105,104,106,98;,
 4;107,108,109,110;,
 4;110,109,111,106;,
 4;103,112,113,114;,
 4;115,116,117,107;,
 4;92,118,119,120;,
 4;121,122,123,124;,
 4;124,125,126,127;,
 4;127,126,112,96;,
 4;66,84,128,129;,
 4;129,128,130,131;,
 4;81,132,133,134;,
 4;134,133,135,130;,
 4;136,137,138,139;,
 4;140,141,132,90;,
 4;85,142,143,144;,
 4;144,143,145,136;,
 4;137,146,147,148;,
 4;149,150,151,135;,
 4;99,98,106,111;,
 3;97,96,112;,
 4;41,40,152,125;,
 4;80,90,132,81;,
 4;108,107,117,153;,
 4;118,92,91,102;,
 4;154,99,111,142;,
 3;145,108,146;,
 3;108,153,146;,
 3;153,155,146;,
 3;155,156,146;,
 4;123,157,49,50;,
 3;158,159,160;,
 3;159,161,160;,
 3;161,118,160;,
 3;118,102,160;,
 3;85,74,142;,
 3;142,74,154;,
 3;74,73,154;,
 4;136,145,146,137;,
 3;135,151,130;,
 3;151,44,130;,
 3;130,44,131;,
 3;44,45,131;,
 3;45,46,131;,
 3;46,47,131;,
 3;47,162,131;,
 4;71,158,160,72;,
 3;97,112,103;,
 4;66,65,79,84;,
 3;157,48,49;,
 3;48,162,47;,
 4;163,152,40,42;,
 4;164,163,42,43;,
 4;44,151,164,43;,
 4;72,160,165,166;,
 4;166,165,154,73;,
 4;118,161,167,119;,
 4;122,168,157,123;,
 4;125,152,169,170;,
 4;171,172,153,117;,
 4;160,102,100,165;,
 4;165,100,99,154;,
 4;142,111,109,143;,
 4;143,109,108,145;,
 4;152,163,173,169;,
 4;172,174,155,153;,
 4;161,159,175,167;,
 4;168,176,48,157;,
 4;146,156,177,147;,
 4;150,178,164,151;,
 4;131,162,179,180;,
 4;181,182,158,71;,
 4;163,164,178,173;,
 4;174,177,156,155;,
 4;162,48,176,179;,
 4;182,175,159,158;,
 4;166,183,69,72;,
 4;68,184,77,65;,
 4;76,183,166,73;,
 4;78,185,83,79;,
 4;83,185,88,80;,
 4;87,186,75,74;,
 3;105,94,97;,
 4;94,187,101,91;,
 4;101,187,105,98;,
 4;104,188,110,106;,
 4;110,188,115,107;,
 3;114,104,103;,
 4;127,189,121,124;,
 4;120,190,93,92;,
 3;95,189,127;,
 3;126,191,113;,
 4;116,192,171,117;,
 4;170,191,126,125;,
 4;70,193,181,71;,
 4;180,194,129,131;,
 4;129,194,67,66;,
 4;134,195,82,81;,
 4;82,195,128,84;,
 4;128,195,134,130;,
 4;144,196,86,85;,
 4;89,197,140,90;,
 4;139,196,144,136;,
 4;141,198,133,132;,
 4;133,198,149,135;,
 4;148,199,138,137;,
 3;126,113,112;,
 3;114,188,104;,
 3;105,187,94;,
 3;95,127,96;,
 4;124,51,41,125;,
 4;124,123,50,51;,
 4;28,62,60,30;,
 4;30,60,59,32;;
 
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
  0.096097;0.396651;-0.912926;,
  -0.407830;-0.446784;0.796278;,
  0.471939;0.314690;-0.823555;,
  -0.049773;-0.282976;0.957835;,
  0.200387;-0.418525;0.885823;,
  0.462638;-0.098376;0.881072;,
  -0.336100;-0.272337;0.901592;,
  -0.016172;0.058000;0.998186;,
  0.011651;0.599033;-0.800639;,
  0.020788;0.644423;-0.764387;,
  -0.887999;0.118744;-0.444249;,
  -0.876272;0.018922;-0.481445;,
  0.710874;0.353924;-0.607780;,
  -0.716468;-0.237490;0.655951;,
  0.313013;-0.205372;0.927278;,
  0.208015;-0.216897;0.953774;,
  0.041119;-0.512920;0.857451;,
  -0.533437;-0.365258;0.762910;,
  -0.738027;-0.301780;0.603527;,
  -0.545823;-0.135626;0.826851;,
  -0.377513;0.135819;0.915990;,
  -0.107171;0.273733;0.955816;,
  0.424089;0.354216;0.833475;,
  0.634499;0.296444;0.713815;,
  0.659351;0.081550;0.747400;,
  0.487274;-0.287276;0.824643;,
  0.343732;-0.393834;0.852492;,
  0.136743;-0.475292;0.869137;,
  0.316384;0.603356;-0.732027;,
  -0.013377;0.589217;-0.807864;,
  -0.592907;0.315698;-0.740808;,
  -0.849837;-0.058721;-0.523764;,
  -0.891569;-0.451715;-0.032530;,
  -0.533531;-0.453176;0.714126;,
  -0.184332;-0.262141;0.947261;,
  -0.158666;0.905658;0.393202;,
  0.154628;0.814773;0.558780;,
  0.600699;0.601071;0.527138;,
  0.691222;0.165597;0.703413;,
  0.618383;0.536462;-0.574291;,
  -0.760383;-0.250807;0.599093;,
  -0.852263;-0.522847;0.016704;,
  -0.825119;-0.431339;-0.364863;,
  -0.645764;-0.335432;-0.685911;,
  0.005409;0.003797;-0.999978;,
  0.462455;0.196850;-0.864514;,
  0.691548;0.157940;-0.704851;,
  0.868511;0.329449;0.370341;,
  0.726154;0.547771;0.415509;,
  0.381580;0.649038;0.658139;,
  0.023286;0.724408;0.688978;,
  -0.403179;0.246480;0.881303;,
  -0.818336;-0.435318;0.375266;,
  -0.843349;-0.432984;0.318257;,
  -0.811773;-0.583387;-0.026178;,
  -0.526583;-0.725676;-0.442837;,
  -0.158442;-0.725605;-0.669622;,
  0.302893;-0.554006;-0.775457;,
  0.671068;-0.279991;-0.686493;,
  0.975988;0.157041;-0.150946;,
  0.771652;0.398049;0.496095;,
  0.522827;0.465481;0.714128;,
  0.076738;0.419996;0.904276;,
  -0.297810;0.345791;0.889797;,
  0.938023;-0.306865;0.161078;,
  0.636161;-0.753751;0.164797;,
  0.511913;-0.527949;0.677654;,
  0.284491;-0.073452;0.955861;,
  0.756685;0.125138;0.641692;,
  0.963182;0.219942;0.154613;,
  -0.548217;-0.823703;0.144815;,
  -0.681837;-0.713539;0.161123;,
  -0.403701;-0.503684;0.763760;,
  0.019286;-0.110581;0.993680;,
  0.357984;-0.608468;0.708247;,
  0.510354;-0.845948;0.154627;,
  0.751322;0.610623;0.250309;,
  0.972880;0.173738;0.152707;,
  0.804749;0.197298;0.559868;,
  0.320752;0.280000;0.904831;,
  0.355327;0.667203;0.654663;,
  0.203551;0.960689;0.188794;,
  -0.762060;0.174269;0.623615;,
  -0.951562;0.166167;0.258686;,
  -0.742609;0.597043;0.303433;,
  -0.255239;0.937469;0.236654;,
  -0.371604;0.641970;0.670660;,
  -0.349924;0.279605;0.894077;,
  0.814805;0.137356;-0.563228;,
  0.974208;0.162493;-0.156572;,
  0.751249;0.609922;-0.252230;,
  0.254710;0.937478;-0.237188;,
  0.373004;0.642914;-0.668976;,
  0.396034;0.119822;-0.910384;,
  -0.743416;0.595699;-0.304097;,
  -0.951817;0.166268;-0.257679;,
  -0.618857;0.172857;-0.766248;,
  -0.134492;0.137709;-0.981299;,
  -0.306368;0.605925;-0.734162;,
  -0.203539;0.960686;-0.188823;,
  0.765514;0.124296;-0.631299;,
  0.145044;-0.038643;-0.988670;,
  0.528207;-0.535606;-0.658881;,
  0.638744;-0.753766;-0.154416;,
  0.940468;-0.307070;-0.145699;,
  0.964019;0.220279;-0.148814;,
  -0.548301;-0.823639;-0.144862;,
  0.510881;-0.846171;-0.151640;,
  0.360844;-0.612159;-0.703600;,
  0.020517;-0.112428;-0.993448;,
  -0.403757;-0.503509;-0.763844;,
  -0.681872;-0.713491;-0.161189;,
  0.215781;0.155691;0.963950;,
  0.747098;0.277633;0.603957;,
  0.979733;0.179303;0.089292;,
  -0.591680;-0.289924;0.752236;,
  -0.850469;-0.500117;0.163050;,
  -0.984715;-0.069495;0.159706;,
  -0.947120;0.279180;0.158183;,
  -0.672945;0.202604;0.711405;,
  -0.187763;0.015064;0.982099;,
  -0.151857;0.202505;0.967435;,
  -0.653643;0.427275;0.624649;,
  -0.910091;0.374665;0.177091;,
  0.986267;0.073673;-0.147815;,
  0.723477;0.184131;-0.665340;,
  0.519143;0.247985;-0.817920;,
  -0.905457;0.317558;-0.281610;,
  -0.619974;0.361235;-0.696521;,
  -0.150203;0.354820;-0.922790;,
  -0.589956;-0.292162;-0.752724;,
  -0.190771;0.015399;-0.981514;,
  -0.676296;0.203449;-0.707978;,
  -0.947250;0.279650;-0.156568;,
  -0.984388;-0.070910;-0.161097;,
  -0.849718;-0.501254;-0.163478;,
  0.320414;0.177001;0.930594;,
  0.804238;0.140426;0.577479;,
  0.985081;0.062669;0.160277;,
  -0.952412;0.244433;0.182110;,
  -0.729475;0.335070;0.596317;,
  -0.298303;0.275927;0.913717;,
  -0.774606;0.574356;-0.264766;,
  -0.557824;0.644506;-0.522920;,
  -0.120362;0.612140;-0.781535;,
  0.975410;0.149075;-0.162334;,
  0.705061;0.374984;-0.601894;,
  0.367331;0.484804;-0.793747;,
  -0.894389;0.418416;-0.158104;,
  -0.637537;0.406914;-0.654193;,
  -0.107582;0.189944;-0.975883;,
  0.958722;0.245752;-0.143035;,
  0.746719;0.251866;-0.615609;,
  0.184986;0.166006;-0.968619;,
  -0.827157;0.533709;-0.175973;,
  -0.570697;0.615585;-0.543470;,
  -0.123675;0.482351;-0.867203;,
  0.985187;0.115959;-0.126333;,
  0.796921;0.238468;-0.555023;,
  0.800717;-0.262444;0.538494;,
  0.368165;-0.601363;0.709096;,
  0.740218;0.400671;0.539945;,
  -0.717144;0.334028;0.611662;,
  0.756027;0.397199;-0.520247;,
  -0.637330;0.328868;-0.696890;,
  0.819744;-0.267275;-0.506541;,
  -0.547917;-0.785903;-0.286607;,
  -0.662514;0.213883;0.717865;,
  -0.944882;-0.075858;-0.318503;,
  0.824432;0.435310;0.361686;,
  -0.187179;0.975784;-0.113183;,
  0.793329;0.436118;-0.424772;,
  0.821289;0.219773;-0.526483;,
  -0.889527;0.217202;-0.401950;,
  -0.587307;-0.528445;0.613038;,
  0.541138;0.465360;-0.700436;,
  0.818638;0.361026;-0.446645;,
  -0.465519;-0.660084;-0.589559;,
  0.052909;-0.546971;-0.835478;,
  -0.341180;0.333401;0.878886;,
  -0.440305;-0.784381;-0.436895;,
  -0.623451;-0.712218;-0.322573;,
  -0.100368;-0.804592;-0.585284;,
  0.324424;-0.670710;-0.667006;,
  0.705820;-0.404999;-0.581201;,
  0.809827;-0.297660;-0.505548;,
  0.530695;-0.836725;0.135106;,
  0.530704;-0.836713;-0.135145;,
  0.020042;0.070619;-0.997302;,
  0.000000;0.000000;-1.000000;,
  -0.076281;0.068376;-0.994739;,
  0.259019;0.308914;-0.915140;,
  0.046480;0.350470;-0.935420;,
  -0.547760;-0.786046;0.286516;,
  0.368074;-0.601245;-0.709244;,
  -0.858071;-0.416583;0.300288;,
  -0.242401;0.091037;-0.965895;;
  188;
  3;26,4,27;,
  4;4,26,25,5;,
  4;16,4,6,17;,
  4;6,4,5,7;,
  3;17,6,18;,
  4;19,6,7,20;,
  3;23,5,24;,
  4;22,7,5,23;,
  3;20,7,21;,
  3;27,4,16;,
  3;5,25,24;,
  3;21,7,22;,
  3;18,6,19;,
  4;30,43,42,31;,
  4;31,42,41,32;,
  4;32,41,40,33;,
  4;33,40,51,34;,
  4;170,170,50,35;,
  4;35,50,49,36;,
  4;36,49,48,37;,
  4;37,48,47,38;,
  4;46,39,171,172;,
  4;45,28,39,46;,
  4;28,45,44,29;,
  4;29,44,43,30;,
  4;8,0,28,29;,
  4;8,29,30,9;,
  4;173,30,31,10;,
  4;11,10,31,32;,
  4;1,174,32,33;,
  4;3,1,33,34;,
  4;15,3,34,15;,
  4;15,15,14,14;,
  4;13,13,13,13;,
  4;175,176,171,12;,
  4;39,2,12,171;,
  4;28,0,2,39;,
  4;41,53,52,40;,
  4;42,54,53,41;,
  4;43,55,54,42;,
  4;177,56,55,43;,
  4;178,57,56,44;,
  4;57,45,46,58;,
  4;58,46,172,59;,
  3;169,60,59;,
  3;61,60,169;,
  4;50,62,61,49;,
  4;51,63,62,50;,
  4;40,179,63,51;,
  4;53,18,19,52;,
  4;54,17,18,53;,
  4;55,180,181,54;,
  4;56,182,180,55;,
  4;57,183,182,56;,
  4;183,57,58,184;,
  4;184,58,59,185;,
  4;60,23,24,59;,
  4;61,22,23,60;,
  4;62,21,22,61;,
  4;63,20,21,62;,
  4;179,19,20,63;,
  4;65,103,104,64;,
  4;64,104,105,69;,
  4;67,73,74,66;,
  4;66,74,75,65;,
  4;71,111,106,70;,
  4;186,187,107,75;,
  4;73,120,115,72;,
  4;72,115,116,71;,
  4;77,89,90,76;,
  4;76,90,91,81;,
  4;79,136,137,78;,
  4;78,137,138,77;,
  4;81,85,86,80;,
  4;80,86,87,79;,
  4;83,139,140,82;,
  4;82,140,141,87;,
  4;85,99,94,84;,
  4;84,94,95,83;,
  4;89,124,125,88;,
  4;88,125,126,93;,
  4;93,97,98,92;,
  4;92,98,99,91;,
  4;103,107,108,102;,
  4;102,108,109,101;,
  4;111,135,130,110;,
  4;110,130,131,109;,
  4;118,133,134,117;,
  4;117,134,135,116;,
  4;120,121,122,119;,
  4;119,122,123,118;,
  4;133,148,149,132;,
  4;132,149,150,131;,
  4;136,79,87,141;,
  3;81,91,99;,
  4;0,8,129,97;,
  4;71,116,135,111;,
  4;139,83,95,127;,
  4;124,89,77,138;,
  4;112,136,141,121;,
  3;123,139,148;,
  3;139,127,148;,
  3;127,142,148;,
  3;142,154,148;,
  4;126,147,175,12;,
  3;151,157,114;,
  3;157,145,114;,
  3;145,124,114;,
  3;124,138,114;,
  3;120,73,121;,
  3;121,73,112;,
  3;73,67,112;,
  4;118,123,148,133;,
  3;131,150,109;,
  3;150,188,109;,
  3;109,188,101;,
  3;188,189,101;,
  3;189,189,101;,
  3;189,190,101;,
  3;190,153,101;,
  4;105,151,114,69;,
  3;81,99,85;,
  4;103,65,75,107;,
  3;147,191,175;,
  3;191,153,190;,
  4;144,129,8,9;,
  4;156,144,9,192;,
  4;188,150,156,192;,
  4;69,114,113,68;,
  4;68,113,112,67;,
  4;124,145,146,125;,
  4;125,146,147,126;,
  4;97,129,128,96;,
  4;96,128,127,95;,
  4;114,138,137,113;,
  4;113,137,136,112;,
  4;121,141,140,122;,
  4;122,140,139,123;,
  4;129,144,143,128;,
  4;128,143,142,127;,
  4;145,157,158,146;,
  4;146,158,191,147;,
  4;148,154,155,149;,
  4;149,155,156,150;,
  4;101,153,152,100;,
  4;100,152,151,105;,
  4;144,156,155,143;,
  4;143,155,154,142;,
  4;153,191,158,152;,
  4;152,158,157,151;,
  4;68,159,64,69;,
  4;64,159,66,65;,
  4;66,159,68,67;,
  4;74,160,186,75;,
  4;70,193,72,71;,
  4;72,160,74,73;,
  3;80,76,81;,
  4;76,161,78,77;,
  4;78,161,80,79;,
  4;86,162,82,87;,
  4;82,162,84,83;,
  3;84,86,85;,
  4;92,163,88,93;,
  4;88,163,90,89;,
  3;90,163,92;,
  3;98,164,94;,
  4;94,164,96,95;,
  4;96,164,98,97;,
  4;104,165,100,105;,
  4;100,165,102,101;,
  4;102,165,104,103;,
  4;110,166,106,111;,
  4;187,194,108,107;,
  4;108,194,110,109;,
  4;119,167,115,120;,
  4;115,195,117,116;,
  4;117,167,119,118;,
  4;134,168,130,135;,
  4;130,196,132,131;,
  4;132,168,134,133;,
  3;98,94,99;,
  3;84,162,86;,
  3;80,161,76;,
  3;90,92,91;,
  4;93,2,0,97;,
  4;93,126,12,2;,
  4;49,61,169,48;,
  4;48,169,59,47;;
 }
 MeshTextureCoords {
  200;
  0.500000;0.634120;,
  0.500000;0.638750;,
  0.531250;0.634120;,
  0.440660;0.634170;,
  0.443820;0.638850;,
  0.531250;0.638750;,
  0.500000;0.643380;,
  0.531250;0.643380;,
  0.446930;0.643450;,
  0.531250;0.645690;,
  0.500000;0.645690;,
  0.448460;0.645730;,
  0.426600;0.638820;,
  0.425040;0.634170;,
  0.428930;0.643430;,
  0.429710;0.645730;,
  0.545490;0.638750;,
  0.542670;0.638750;,
  0.542670;0.643380;,
  0.545490;0.643380;,
  0.542670;0.646540;,
  0.545490;0.646750;,
  0.500000;0.646540;,
  0.500000;0.646750;,
  0.449020;0.646560;,
  0.449160;0.646760;,
  0.423420;0.646560;,
  0.421870;0.646760;,
  0.422350;0.643420;,
  0.420730;0.643420;,
  0.420300;0.638820;,
  0.418750;0.638810;,
  0.418170;0.632460;,
  0.416470;0.632040;,
  0.439510;0.632460;,
  0.439220;0.632040;,
  0.500000;0.632430;,
  0.500000;0.632010;,
  0.542670;0.632430;,
  0.545490;0.632010;,
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
  0.538800;0.646250;,
  0.500000;0.646250;,
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
  0.382110;0.765920;,
  0.375000;0.760020;,
  0.375000;0.990560;,
  0.365560;-0.000000;,
  0.135020;-0.000000;,
  0.140920;0.009740;,
  0.360200;0.009050;,
  0.382200;0.009860;,
  0.499050;0.006520;,
  0.495120;-0.000000;,
  0.379050;-0.000000;,
  0.379050;1.000000;,
  0.495120;1.000000;,
  0.493170;0.984700;,
  0.509210;0.984700;,
  0.509210;0.765300;,
  0.501650;0.764910;,
  0.501650;0.985070;,
  0.493170;0.765300;,
  0.612940;0.009690;,
  0.618980;-0.000000;,
  0.507200;-0.000000;,
  0.507200;1.000000;,
  0.618980;1.000000;,
  0.617430;0.983870;,
  0.349690;0.244110;,
  0.150310;0.244110;,
  0.133710;0.258710;,
  0.250000;0.375000;,
  0.366290;0.491290;,
  0.395450;0.474690;,
  0.395450;0.275310;,
  0.395450;0.244110;,
  0.395580;0.120510;,
  0.375000;0.120510;,
  0.373130;0.244320;,
  0.349410;0.120510;,
  0.604550;0.275310;,
  0.604860;0.254610;,
  0.395140;0.254610;,
  0.604550;0.244110;,
  0.650310;0.244110;,
  0.650010;0.120510;,
  0.625000;0.120510;,
  0.626870;0.244310;,
  0.604300;0.120510;,
  0.604550;0.474690;,
  0.625000;0.483640;,
  0.625000;0.266370;,
  0.641370;0.250000;,
  0.858640;0.250000;,
  0.849690;0.244110;,
  0.162650;0.120510;,
  0.125000;0.120510;,
  0.125000;0.245370;,
  0.375000;0.504630;,
  0.375000;0.629490;,
  0.390260;0.629490;,
  0.395450;0.505890;,
  0.604550;0.505890;,
  0.604860;0.495390;,
  0.395190;0.495390;,
  0.498800;0.750540;,
  0.381070;0.749320;,
  0.504690;0.742310;,
  0.382200;0.740140;,
  0.617430;0.766130;,
  0.616000;0.749620;,
  0.509260;0.751110;,
  0.612940;0.740310;,
  0.641350;0.006170;,
  0.858870;0.006090;,
  0.864460;-0.000000;,
  0.635600;-0.000000;,
  0.625000;0.989400;,
  0.625000;0.760540;,
  0.609450;0.101990;,
  0.625000;0.101990;,
  0.624910;0.006830;,
  0.641040;0.101990;,
  0.857880;0.101990;,
  0.875000;0.101990;,
  0.875000;0.005140;,
  0.625000;0.744850;,
  0.625000;0.648010;,
  0.618370;0.648010;,
  0.616540;0.629490;,
  0.849350;0.120510;,
  0.391360;0.101990;,
  0.858130;0.109910;,
  0.858100;0.105280;,
  0.407100;0.638800;,
  0.144100;0.101990;,
  0.141440;0.106090;,
  0.358270;0.101990;,
  0.150750;0.110720;,
  0.387810;0.648010;,
  0.617320;0.638750;,
  0.617540;0.643380;,
  0.375000;0.101990;,
  0.373130;0.006160;,
  0.125000;0.111250;,
  0.375000;0.638750;,
  0.625000;0.629490;,
  0.625000;0.504690;,
  0.875000;0.245310;,
  0.875000;0.120510;,
  0.625000;0.638750;,
  0.875000;0.111250;,
  0.125000;0.106620;,
  0.375000;0.643380;,
  0.875000;0.106620;,
  0.625000;0.643380;,
  0.375000;0.648010;,
  0.375000;0.744390;,
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
