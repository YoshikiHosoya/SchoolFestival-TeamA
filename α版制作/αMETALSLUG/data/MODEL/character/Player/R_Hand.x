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
 -3.92536;-1.74053;-1.39807;,
 -3.21490;-0.72652;-1.39807;,
 -3.21490;-0.72652;-0.02308;,
 -3.92536;-1.74053;-0.02308;,
 -1.94679;-1.15191;-0.95766;,
 -1.94679;-1.15191;-0.02280;,
 -1.34421;0.17053;-1.93638;,
 -1.94679;0.17053;-1.89253;,
 -1.94679;0.67995;-1.89253;,
 -1.34421;0.67995;-1.93638;,
 -1.34421;-0.44752;-1.93638;,
 -1.94679;-0.44848;-1.89253;,
 -3.92536;-1.74053;1.35191;,
 -3.21490;-0.72652;1.35191;,
 -3.08641;-0.50950;1.46870;,
 -3.35062;-1.06037;1.73533;,
 -0.04889;0.17053;-1.12195;,
 -0.04889;-0.44752;-1.12195;,
 -0.04889;0.67995;-1.12195;,
 -1.94679;-1.15191;0.91207;,
 -3.10782;-0.65723;2.00890;,
 -2.95939;-0.34121;1.73945;,
 -1.94679;-0.44752;1.84691;,
 -4.41710;0.19847;2.72686;,
 -3.23654;-0.79940;1.99681;,
 -4.65091;-0.65260;2.72686;,
 -2.02861;1.09328;-1.47708;,
 -1.97077;0.99136;-1.77085;,
 -5.24493;1.33754;-2.63959;,
 -5.18187;1.45520;-2.31037;,
 -1.94679;0.74535;-1.89253;,
 -5.45153;1.10930;-2.77303;,
 -0.96788;0.74535;1.88692;,
 -1.00266;0.99136;1.74543;,
 -1.96879;0.99136;1.72449;,
 -1.94679;0.74535;1.84691;,
 -1.08669;1.09328;1.40382;,
 -2.02181;1.09328;1.42887;,
 -1.94679;-1.15191;1.42133;,
 -1.94679;-0.69843;1.72226;,
 -2.97617;-0.47367;1.71430;,
 -6.56926;-3.18171;2.37195;,
 -6.80734;-3.07435;2.37173;,
 -6.80719;-3.07531;-2.39188;,
 -6.56997;-3.18161;-2.37321;,
 -6.80734;-3.07435;2.37173;,
 -6.95194;-2.85685;2.37195;,
 -6.95076;-2.86052;-2.39862;,
 -6.80719;-3.07531;-2.39188;,
 -6.60502;-2.83604;2.72686;,
 -6.56526;-3.07723;2.62411;,
 -4.53047;-3.37358;2.62465;,
 -4.45750;-3.14147;2.72686;,
 -6.56526;-3.07723;2.62411;,
 -4.55096;-3.47305;2.37685;,
 -4.53047;-3.37358;2.62465;,
 -6.84954;-2.83598;2.62411;,
 -7.58177;-0.52670;2.62551;,
 -7.67670;-0.56633;2.37330;,
 -7.37309;-0.40146;2.72686;,
 -4.12238;-3.22234;2.37473;,
 -4.29348;-3.42261;2.37640;,
 -4.29341;-3.42367;-2.17306;,
 -4.12375;-3.22585;-2.15922;,
 -4.54907;-3.47334;-2.19272;,
 -4.28701;-1.73692;-2.50519;,
 -4.02943;-1.73947;-2.38635;,
 -3.96253;-2.18785;-2.39830;,
 -4.12964;-2.37169;-2.50221;,
 -4.02943;-1.73947;-2.38635;,
 -3.92536;-1.74053;-2.13934;,
 -3.84964;-2.14396;-2.13081;,
 -3.96253;-2.18785;-2.39830;,
 -3.20963;-0.90452;1.86650;,
 -4.04694;-1.69054;2.61052;,
 -3.92536;-1.74053;2.32961;,
 -4.34049;-1.56982;2.72686;,
 -5.66540;1.29571;2.34891;,
 -5.43639;1.41463;2.32848;,
 -5.43254;1.41569;-2.36404;,
 -5.66351;1.29708;-2.38136;,
 -5.18563;1.45520;2.27063;,
 -5.34366;1.11487;2.69340;,
 -5.57367;1.20154;2.63162;,
 -7.47053;-0.17860;2.62481;,
 -7.52533;-0.09184;2.37611;,
 -7.67656;-0.30423;2.37554;,
 -7.67603;-0.30385;-2.42179;,
 -7.67670;-0.56633;-2.41946;,
 -7.52333;-0.09037;-2.41946;,
 -5.60805;1.19432;-2.67817;,
 -7.47010;-0.17837;-2.67286;,
 -7.37309;-0.40146;-2.77303;,
 -7.58090;-0.52820;-2.67030;,
 -7.20461;-1.70770;-2.65148;,
 -7.31590;-1.70658;-2.39869;,
 -6.94300;-1.71033;-2.74007;,
 -3.99759;-2.58286;-2.39856;,
 -4.21788;-3.19383;-2.39709;,
 -4.45649;-3.13978;-2.51283;,
 -3.89711;-2.64753;-2.13078;,
 -3.84980;-2.14310;2.36799;,
 -3.83784;-2.39611;2.37163;,
 -3.83695;-2.39918;1.35191;,
 -3.84833;-2.15099;1.35191;,
 -3.83784;-2.39611;2.37163;,
 -3.89745;-2.64836;2.36799;,
 -3.89452;-2.64088;1.35191;,
 -3.83695;-2.39918;1.35191;,
 -4.00366;-2.58421;2.62877;,
 -4.01237;-2.66849;2.62276;,
 -3.93057;-2.73290;2.37138;,
 -4.00366;-2.58421;2.62877;,
 -4.14341;-2.37028;2.72686;,
 -4.20980;-2.51293;2.72686;,
 -4.01237;-2.66849;2.62276;,
 -6.56149;-3.07352;-2.62546;,
 -4.53044;-3.37230;-2.42119;,
 -6.59719;-2.82357;-2.72931;,
 -5.45153;0.19847;-2.77303;,
 -6.57095;-0.65260;-2.77303;,
 -0.04889;-0.45439;-1.12195;,
 -0.04889;-0.45439;-0.02280;,
 -0.04889;0.74535;-1.12195;,
 -0.04889;0.74535;1.07636;,
 -0.04889;-0.45439;1.07636;,
 -0.39687;-1.15191;-0.02280;,
 -0.39687;-1.15191;-0.79363;,
 -0.96788;-0.45439;1.88692;,
 -3.60398;-0.07785;-2.30449;,
 -3.84833;-2.15099;-1.39807;,
 -3.84833;-2.15099;-0.02308;,
 -1.34421;0.74535;-1.93638;,
 -1.34421;-0.45439;-1.93638;,
 -0.96788;0.74535;1.88692;,
 -0.96788;-0.45439;1.88692;,
 -1.08669;-1.15191;1.40382;,
 -0.39687;-1.15191;0.79535;,
 -3.89452;-2.64088;-1.39807;,
 -3.89452;-2.64088;-0.02308;,
 -0.39687;1.09328;0.79535;,
 -0.39687;1.09328;-0.79363;,
 -1.44511;1.09328;-1.45273;,
 -3.21490;-0.72652;-1.97429;,
 -1.94679;-1.15191;-1.45583;,
 -1.44511;-1.15191;-1.45273;,
 -1.37377;-0.70041;-1.79472;,
 -0.15082;-0.70041;-1.02581;,
 -1.37377;-0.70041;-1.79472;,
 -0.15082;-0.70041;-1.02581;,
 -1.94679;-0.69900;-1.76462;,
 -1.94679;-0.69900;-1.76462;,
 -1.37377;0.99136;-1.79472;,
 -0.15082;0.99136;0.99406;,
 -1.00266;0.99136;1.74543;,
 -0.15082;0.99136;0.99406;,
 -5.20073;1.32806;2.57424;,
 -1.00266;-0.70041;1.74543;,
 -1.00266;-0.70041;1.74543;,
 -0.15082;-0.70041;0.99406;,
 -0.15082;-0.70041;0.99406;,
 -3.33754;-0.31015;-2.26278;,
 -3.33754;-0.31015;-2.26278;,
 -3.96566;-2.18647;2.62861;,
 -6.84436;-2.83124;-2.64636;,
 -4.21925;-3.19181;2.62401;,
 -4.21925;-3.19181;2.62401;,
 -0.15082;-0.70041;-0.02280;,
 -0.15082;-0.70041;-0.02280;,
 -3.83695;-2.39918;-0.02308;,
 -3.83695;-2.39918;-0.02308;,
 -3.83695;-2.39918;-1.39807;,
 -3.83695;-2.39918;-1.39807;,
 -3.83804;-2.39975;-2.12649;,
 -3.83804;-2.39975;-2.12649;,
 -0.15082;0.99136;-1.02581;,
 -0.15082;0.99136;-1.02581;,
 -6.76545;-3.02494;2.57798;,
 -6.76545;-3.02494;2.57798;,
 -4.32537;-3.36828;2.57894;,
 -4.32537;-3.36828;2.57894;,
 -5.40680;1.33470;2.56830;,
 -7.61626;-0.32306;2.57930;,
 -5.42456;1.33812;-2.61766;,
 -7.61561;-0.32347;-2.62645;,
 -3.91696;-2.39365;-2.35170;,
 -3.91696;-2.39365;-2.35170;,
 -3.92609;-2.37517;2.58872;,
 -3.92609;-2.37517;2.58872;,
 -6.76170;-3.02286;-2.59609;,
 -4.32253;-3.36914;-2.36062;;
 
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
  0.241899;0.000000;-0.970301;,
  0.086636;0.000000;-0.996240;,
  0.086636;0.000000;-0.996240;,
  0.089697;-0.109097;-0.989976;,
  0.149938;-0.088905;-0.984690;,
  0.091875;-0.096570;-0.991077;,
  0.117982;-0.006279;0.992996;,
  0.263761;-0.141485;0.954155;,
  0.102662;-0.232781;0.967095;,
  0.977438;-0.211224;-0.000000;,
  0.818985;-0.573814;-0.000000;,
  -0.161120;-0.986935;0.000000;,
  0.977438;-0.211221;0.000002;,
  0.818985;-0.573814;-0.000000;,
  -0.161120;-0.986935;0.000000;,
  0.875294;0.000000;-0.483591;,
  0.875294;0.000000;-0.483591;,
  0.954294;-0.297051;-0.032914;,
  0.833669;-0.547013;-0.075981;,
  -0.160079;-0.977031;0.140660;,
  0.154297;-0.812814;-0.561717;,
  0.212285;-0.550117;-0.807655;,
  0.234739;-0.258560;-0.937040;,
  -0.054161;-0.881216;-0.469601;,
  0.079254;-0.450932;-0.889033;,
  0.236749;0.256508;-0.937099;,
  0.158160;0.784536;-0.599574;,
  0.032223;0.993074;-0.112983;,
  0.101229;0.218493;-0.970574;,
  0.111828;0.744581;-0.658098;,
  0.077125;0.983949;-0.160921;,
  0.041890;0.993137;0.109194;,
  0.212324;0.787319;0.578833;,
  0.325411;0.257884;0.909727;,
  0.129269;0.260979;0.956650;,
  0.117501;0.745007;0.656627;,
  0.062100;0.989413;0.131168;,
  0.205697;-0.813650;0.543749;,
  0.289017;-0.547878;0.785047;,
  0.324564;-0.258015;0.909992;,
  -0.116706;-0.536216;0.835974;,
  -0.162441;-0.833193;0.528585;,
  -0.636767;-0.751079;0.174380;,
  -0.266643;-0.946509;0.181718;,
  -0.238085;-0.699286;0.674029;,
  -0.198420;-0.233659;0.951858;,
  -0.651753;-0.348564;0.673588;,
  -0.890515;-0.417230;0.181392;,
  0.055809;-0.729605;0.681588;,
  0.015561;-0.983383;0.180875;,
  0.496563;-0.850380;0.174009;,
  0.848310;-0.498466;0.178613;,
  0.609131;-0.408099;0.680010;,
  0.096328;-0.165214;0.981542;,
  0.416079;-0.891231;0.180514;,
  0.788514;-0.509444;0.344547;,
  0.887262;-0.237141;0.395640;,
  0.819623;-0.504667;-0.271163;,
  0.384032;-0.302855;-0.872238;,
  0.200282;-0.093141;-0.975301;,
  0.952186;-0.173525;-0.251457;,
  0.651580;-0.047569;-0.757087;,
  0.172862;0.027799;-0.984554;,
  0.818599;-0.571905;-0.053101;,
  0.820307;-0.522916;-0.231636;,
  -0.219763;-0.542487;0.810809;,
  0.132077;-0.404658;0.904880;,
  0.605435;-0.317703;0.729735;,
  0.619421;-0.126188;0.774851;,
  0.873538;-0.450743;0.183747;,
  0.957498;-0.235079;0.167136;,
  0.771078;-0.106908;0.627702;,
  0.399200;0.041266;0.915935;,
  0.110168;0.741557;0.661783;,
  0.032513;0.983795;0.176325;,
  -0.279231;0.941755;0.187421;,
  -0.521519;0.830033;0.197645;,
  -0.329782;0.631270;0.701956;,
  0.053599;0.230556;0.971582;,
  -0.538394;0.480086;0.692567;,
  -0.694834;0.694626;0.186280;,
  -0.937929;0.300426;0.173303;,
  -0.970660;-0.208510;0.119757;,
  -0.731492;-0.077635;0.677416;,
  -0.180883;0.057290;0.981835;,
  -0.292393;0.942393;-0.162486;,
  0.022618;0.986497;-0.162211;,
  0.071404;0.768337;-0.636050;,
  0.109065;0.169896;-0.979408;,
  -0.380212;0.667136;-0.640600;,
  -0.526878;0.831526;-0.175968;,
  -0.937867;0.300762;-0.173057;,
  -0.695770;0.696051;-0.177248;,
  -0.556378;0.496741;-0.666103;,
  -0.228559;0.070375;-0.970983;,
  -0.723908;-0.085133;-0.684623;,
  -0.970141;-0.160631;-0.181723;,
  0.977812;-0.091970;-0.188215;,
  0.935711;-0.295390;-0.192845;,
  0.728891;-0.203898;-0.653562;,
  0.371411;-0.028569;-0.928029;,
  0.751342;0.072400;-0.655929;,
  0.973945;0.116889;-0.194341;,
  -0.933649;-0.298091;-0.198599;,
  -0.657429;-0.218501;-0.721141;,
  -0.055001;-0.043669;-0.997531;,
  0.974529;-0.087938;0.206302;,
  0.971114;0.125580;0.202896;,
  0.731410;0.081698;0.677026;,
  0.339088;-0.023777;0.940454;,
  0.717352;-0.172214;0.675091;,
  0.942913;-0.312650;0.114738;,
  0.913350;-0.315402;0.257512;,
  0.677912;-0.228873;0.698608;,
  0.192516;-0.072591;0.978605;,
  -0.615789;-0.345209;-0.708262;,
  -0.072517;-0.176344;-0.981654;,
  -0.174692;-0.694208;-0.698253;,
  -0.249828;-0.948951;-0.192557;,
  -0.628081;-0.755384;-0.186839;,
  -0.905030;-0.396385;-0.154269;,
  0.504015;-0.843945;-0.183647;,
  0.031042;-0.980659;-0.193249;,
  0.110672;-0.712445;-0.692946;,
  0.180558;-0.194154;-0.964211;,
  0.628468;-0.391500;-0.672128;,
  0.884084;-0.450570;-0.124025;,
  0.000000;-1.000000;0.000000;,
  0.902231;-0.431253;-0.000000;,
  0.995276;-0.097089;-0.000000;,
  0.384626;-0.900842;-0.201362;,
  0.747126;-0.534639;-0.394923;,
  0.850328;-0.251882;-0.462058;,
  0.993298;0.115582;0.000228;,
  0.995622;-0.093468;0.000567;,
  0.961004;-0.276533;0.000446;,
  0.993319;0.115403;0.000000;,
  0.995585;-0.093866;-0.000000;,
  0.954190;-0.299201;-0.000000;,
  0.993326;0.115339;-0.000360;,
  0.995576;-0.093955;-0.000694;,
  0.949942;-0.312426;-0.000259;,
  0.199872;0.976618;0.079176;,
  0.590652;0.766379;0.252575;,
  0.929995;0.188976;0.315272;,
  0.137829;0.988379;-0.064104;,
  0.551771;0.784245;-0.283740;,
  0.908112;0.200422;-0.367647;,
  -0.541009;-0.637373;0.548694;,
  0.419287;-0.715880;0.558313;,
  -0.175648;0.802081;0.570801;,
  -0.793049;0.254059;0.553649;,
  -0.231732;0.828681;-0.509497;,
  -0.793787;0.251370;-0.553819;,
  0.838183;-0.077290;-0.539885;,
  0.816367;-0.072598;0.572952;,
  -0.503312;-0.639780;-0.580826;,
  0.443904;-0.694345;-0.566422;,
  -0.318031;-0.948080;0.000000;,
  -0.318031;-0.948080;0.000000;,
  -0.319038;-0.905332;0.280335;,
  -0.301272;-0.760846;0.574760;,
  -0.254436;-0.065152;0.964892;,
  -0.318031;-0.948080;0.000000;,
  0.887795;-0.449530;0.098705;,
  0.148256;-0.545181;-0.825105;,
  0.878076;-0.478522;-0.000000;,
  0.742258;-0.664998;-0.082653;,
  0.934934;-0.176889;0.307584;;
  180;
  4;12,13,10,9;,
  4;158,14,11,159;,
  4;0,1,2,0;,
  4;0,3,1,0;,
  4;17,18,64,63;,
  4;16,15,0,0;,
  4;15,16,0,0;,
  4;9,10,18,17;,
  4;159,11,19,160;,
  4;67,66,8,7;,
  4;68,67,7,6;,
  4;30,29,87,86;,
  4;29,28,88,87;,
  4;33,32,35,34;,
  4;32,31,36,35;,
  4;41,40,65,161;,
  4;40,8,66,65;,
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
  4;88,4,5,94;,
  3;84,6,78;,
  3;132,15,129;,
  3;15,16,129;,
  3;16,15,129;,
  3;15,147,129;,
  3;147,144,129;,
  3;144,56,129;,
  4;7,8,34,78;,
  3;4,88,3;,
  3;88,28,2;,
  3;88,2,1;,
  3;1,3,88;,
  4;127,11,14,130;,
  4;33,34,8,39;,
  3;94,5,105;,
  3;5,59,105;,
  3;59,62,105;,
  3;53,84,45;,
  4;139,12,9,136;,
  4;0,2,28,25;,
  3;22,3,0;,
  3;162,162,162;,
  4;72,6,114,109;,
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
  4;60,12,139,102;,
  4;57,13,12,60;,
  4;23,14,158,163;,
  4;130,14,23,20;,
  4;15,132,22,0;,
  4;147,15,0,25;,
  4;136,9,17,133;,
  4;54,19,11,127;,
  3;72,68,6;,
  3;17,63,70;,
  3;5,4,59;,
  3;105,62,116;,
  3;116,62,124;,
  3;62,100,124;,
  3;53,114,6;,
  3;53,6,84;,
  3;78,6,7;,
  4;126,111,112,51;,
  3;69,64,164;,
  4;20,21,131,130;,
  4;21,22,132,131;,
  4;22,21,24,3;,
  4;21,20,23,24;,
  4;27,26,29,30;,
  4;26,25,28,29;,
  4;31,32,143,142;,
  4;32,33,144,143;,
  4;34,35,73,78;,
  4;35,36,74,73;,
  4;37,38,40,41;,
  4;38,39,8,40;,
  4;39,38,55,56;,
  4;38,37,54,55;,
  4;3,24,58,59;,
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
