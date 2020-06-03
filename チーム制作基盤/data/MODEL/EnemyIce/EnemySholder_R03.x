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
 68;
 -4.57258;-0.39059;-5.10965;,
 -8.43952;-0.20203;-5.88640;,
 -8.33211;3.75541;-4.23765;,
 -4.47192;2.48350;-3.24036;,
 -3.54048;1.38986;1.57015;,
 0.61120;-0.88425;-2.18923;,
 -4.39449;3.28246;-1.25513;,
 -8.07776;2.73248;3.69661;,
 -8.15413;-1.34972;3.01580;,
 -2.26997;-1.14592;0.36948;,
 -22.65851;-0.49737;-1.02948;,
 -12.56926;-1.27633;3.23585;,
 -17.04816;1.26396;2.80487;,
 -8.21122;4.37016;-0.89319;,
 -7.76677;-4.44475;-0.13459;,
 -8.39568;-5.49059;-2.53773;,
 -4.52341;-3.60972;-2.40457;,
 -2.36757;-2.11015;-0.43767;,
 -16.59097;2.24371;-2.89581;,
 -19.55664;1.87367;-0.77792;,
 -8.45953;-3.05605;-5.37364;,
 -4.59155;-1.40433;-5.27872;,
 -12.80645;-5.18385;-2.27875;,
 -12.88750;-3.66883;-5.26804;,
 -14.82732;-2.83631;1.34493;,
 -12.84095;-0.18365;-5.23939;,
 -10.60440;-3.35287;-5.32250;,
 -10.57285;-0.18766;-5.61512;,
 -10.47072;3.79098;-4.13108;,
 -10.34409;4.71323;-0.73532;,
 -12.86075;2.90514;3.20840;,
 -10.29273;-1.31416;3.12238;,
 -10.38770;-3.71480;1.23867;,
 -10.54683;-6.12448;-2.54278;,
 -7.74615;-10.97697;0.47037;,
 -6.87968;-13.69039;0.50927;,
 -7.59664;-13.69039;-2.85966;,
 -8.85253;-10.97697;-2.07191;,
 -13.27652;-10.42382;-1.90613;,
 -10.58714;-7.38198;0.34282;,
 -10.43763;-10.97697;-2.98721;,
 -14.69913;-13.69039;-3.17854;,
 -14.84864;-13.69039;0.15150;,
 -12.74563;-9.47476;0.24591;,
 -10.58714;-23.84267;0.34282;,
 -14.84864;-16.81362;0.15150;,
 -13.82918;-19.98914;-1.70818;,
 -10.40014;-13.69039;-3.82245;,
 -12.68726;-13.31327;3.04027;,
 -10.76129;-13.69039;4.22134;,
 -10.69005;-10.97697;2.63501;,
 -12.21519;-9.51552;1.12560;,
 -8.70726;-19.53957;-1.68578;,
 -10.49844;-21.68049;-1.63280;,
 -7.84611;-13.69039;2.69674;,
 -7.78328;-10.97697;1.29735;,
 -10.75274;-16.81362;4.03101;,
 -7.87122;-16.81362;3.25647;,
 -13.39655;-18.34845;1.70004;,
 -7.26189;-16.81362;0.49212;,
 -7.85829;-15.20325;2.96786;,
 -7.02713;-15.20325;0.50265;,
 -7.59664;-15.20325;-2.85966;,
 -10.38888;-15.20325;-4.07331;,
 -14.04975;-17.05738;-3.14938;,
 -14.84864;-15.20325;0.15150;,
 -13.64350;-15.20325;2.32085;,
 -10.78578;-15.20325;4.76744;;
 
 80;
 4;0,1,2,3;,
 3;4,5,6;,
 4;7,8,9,4;,
 3;10,11,12;,
 4;6,13,7,4;,
 4;14,15,16,17;,
 3;5,3,6;,
 4;2,13,6,3;,
 3;18,10,19;,
 4;16,15,20,21;,
 3;22,10,23;,
 3;24,11,10;,
 4;17,9,8,14;,
 3;17,5,9;,
 3;21,5,16;,
 4;20,1,0,21;,
 3;5,0,3;,
 3;16,5,17;,
 3;21,0,5;,
 3;9,5,4;,
 3;25,10,18;,
 3;24,10,22;,
 3;10,12,19;,
 3;23,10,25;,
 4;26,27,1,20;,
 4;2,1,27,28;,
 4;28,29,13,2;,
 4;7,13,29,30;,
 4;30,31,8,7;,
 4;14,8,31,32;,
 4;32,33,15,14;,
 4;20,15,33,26;,
 4;23,25,27,26;,
 4;28,27,25,18;,
 4;18,19,29,28;,
 4;30,29,19,12;,
 4;11,31,30,12;,
 4;32,31,11,24;,
 4;24,22,33,32;,
 4;26,33,22,23;,
 4;34,35,36,37;,
 3;38,39,40;,
 4;41,42,43,38;,
 3;44,45,46;,
 4;40,47,41,38;,
 4;48,49,50,51;,
 3;39,37,40;,
 4;36,47,40,37;,
 3;52,44,53;,
 4;50,49,54,55;,
 3;56,44,57;,
 3;58,45,44;,
 4;51,43,42,48;,
 3;51,39,43;,
 3;55,39,50;,
 4;54,35,34,55;,
 3;39,34,37;,
 3;50,39,51;,
 3;55,34,39;,
 3;43,39,38;,
 3;59,44,52;,
 3;58,44,56;,
 3;44,46,53;,
 3;57,44,59;,
 4;60,61,35,54;,
 4;36,35,61,62;,
 4;62,63,47,36;,
 4;41,47,63,64;,
 4;64,65,42,41;,
 4;48,42,65,66;,
 4;66,67,49,48;,
 4;54,49,67,60;,
 4;57,59,61,60;,
 4;62,61,59,52;,
 4;52,53,63,62;,
 4;64,63,53,46;,
 4;45,65,64,46;,
 4;66,65,45,58;,
 4;58,56,67,66;,
 4;60,67,56,57;;
 
 MeshMaterialList {
  1;
  80;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.533333;0.687059;0.800000;0.890000;;
   11.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game314\\Documents\\Visual Studio 2015\\Projects\\C++3D2nd\\data\\Texture\\Ice.jpg";
   }
  }
 }
 MeshNormals {
  88;
  -0.301219;-0.471470;-0.828845;,
  -0.371302;0.610716;-0.699400;,
  0.393009;-0.370004;-0.841808;,
  0.423645;0.689113;-0.587918;,
  0.461089;-0.767567;0.445239;,
  0.625513;0.580466;0.521338;,
  -0.262493;-0.729456;0.631657;,
  -0.206761;-0.270802;0.940168;,
  0.441781;-0.874183;-0.201579;,
  0.497736;0.867261;0.010832;,
  -0.389937;0.901441;-0.188024;,
  -0.325851;-0.944800;-0.034252;,
  -0.279924;0.155681;-0.947315;,
  -0.385110;-0.630274;0.674126;,
  -0.214438;-0.423550;0.880126;,
  0.517395;-0.369400;0.771911;,
  0.634622;0.604242;-0.481816;,
  0.358677;0.269427;-0.893734;,
  0.158299;-0.434834;-0.886488;,
  0.072044;0.174932;-0.981941;,
  0.153556;0.754745;-0.637793;,
  0.212881;0.975118;0.061851;,
  0.186778;-0.160244;0.969245;,
  0.210499;-0.425287;0.880239;,
  0.257796;-0.792893;0.552144;,
  0.308302;-0.936272;-0.168359;,
  -0.038618;-0.466275;-0.883796;,
  -0.117635;0.147810;-0.981995;,
  -0.143364;0.748747;-0.647167;,
  -0.121677;0.991512;0.045815;,
  -0.125204;0.937406;0.324952;,
  0.001216;-0.380104;0.924943;,
  -0.000764;-0.780465;0.625199;,
  -0.030366;-0.878603;0.476586;,
  0.708010;-0.293007;0.642548;,
  0.782258;-0.415494;-0.464152;,
  0.693258;0.501039;0.518028;,
  0.641497;0.515568;-0.568041;,
  -0.544891;0.519708;0.658026;,
  -0.379697;0.647835;-0.660409;,
  -0.710763;-0.334306;0.618914;,
  -0.949830;-0.303103;0.077153;,
  0.022903;0.512429;0.858424;,
  0.116392;0.530787;-0.839474;,
  0.168889;-0.521175;-0.836572;,
  -0.118535;-0.347271;0.930243;,
  0.955661;-0.290184;0.050058;,
  -0.718530;-0.482163;0.501232;,
  -0.916855;-0.305590;0.256889;,
  -0.795440;0.570562;0.204290;,
  0.505700;0.715406;-0.482142;,
  0.873381;0.478738;-0.089528;,
  0.752277;0.241363;0.613044;,
  0.988038;0.150840;0.032075;,
  0.740246;0.211946;-0.638056;,
  0.099298;0.218824;-0.970699;,
  -0.983555;0.173595;-0.049850;,
  -0.943136;0.214501;0.253936;,
  -0.664782;0.287319;0.689575;,
  -0.017316;0.368534;0.929453;,
  0.756145;0.013223;0.654271;,
  0.994058;-0.089266;0.062284;,
  0.765156;-0.150102;-0.626103;,
  0.125061;-0.157822;-0.979516;,
  -0.135500;-0.174857;-0.975226;,
  -0.978315;-0.048418;0.201382;,
  -0.733461;-0.023038;0.679341;,
  -0.294521;-0.073493;0.952815;,
  0.393547;-0.187896;0.899898;,
  0.223898;0.901175;0.371151;,
  -0.444570;0.335982;-0.830345;,
  -0.434768;-0.807967;-0.397702;,
  0.630819;-0.538167;0.558967;,
  0.405960;-0.720369;-0.562374;,
  -0.551260;0.668165;0.499668;,
  -0.448538;0.804252;0.389862;,
  -0.026075;-0.060072;0.997853;,
  0.010826;-0.774737;-0.632191;,
  -0.903095;0.429360;-0.008375;,
  -0.191238;0.214219;-0.957882;,
  0.856823;-0.492197;-0.153611;,
  0.232120;-0.447647;0.863558;,
  -0.600458;0.694142;0.397010;,
  0.363618;0.493399;0.790151;,
  -0.306506;-0.635191;-0.708933;,
  -0.196612;-0.525315;-0.827882;,
  -0.983032;-0.092827;-0.158214;,
  0.481246;0.220512;0.848396;;
  80;
  4;17,19,20,3;,
  3;5,16,9;,
  4;22,23,15,68;,
  3;13,14,7;,
  4;9,21,69,5;,
  4;24,25,8,4;,
  3;16,3,9;,
  4;20,21,9,3;,
  3;1,70,10;,
  4;8,25,18,2;,
  3;11,71,0;,
  3;6,14,13;,
  4;4,15,23,24;,
  3;4,72,15;,
  3;2,73,8;,
  4;18,19,17,2;,
  3;16,17,3;,
  3;8,72,4;,
  3;2,17,16;,
  3;15,72,5;,
  3;12,70,1;,
  3;6,13,11;,
  3;74,75,74;,
  3;0,70,12;,
  4;26,27,19,18;,
  4;20,19,27,28;,
  4;28,29,21,20;,
  4;69,21,29,30;,
  4;76,31,23,22;,
  4;24,23,31,32;,
  4;32,33,25,24;,
  4;18,25,77,26;,
  4;0,12,27,26;,
  4;28,27,12,1;,
  4;1,10,29,28;,
  4;30,29,10,75;,
  4;14,31,76,7;,
  4;32,31,14,6;,
  4;6,11,33,32;,
  4;26,77,11,0;,
  4;51,53,54,37;,
  3;39,50,43;,
  4;56,57,49,78;,
  3;47,48,41;,
  4;43,55,79,39;,
  4;58,59,42,38;,
  3;50,37,43;,
  4;54,55,43,37;,
  3;35,80,44;,
  4;42,59,52,36;,
  3;45,81,34;,
  3;40,48,47;,
  4;38,49,57,58;,
  3;38,82,49;,
  3;36,83,42;,
  4;52,53,51,36;,
  3;50,51,37;,
  3;42,82,38;,
  3;36,51,50;,
  3;49,82,39;,
  3;46,80,35;,
  3;40,47,45;,
  3;84,85,44;,
  3;34,80,46;,
  4;60,61,53,52;,
  4;54,53,61,62;,
  4;62,63,55,54;,
  4;79,55,63,64;,
  4;86,65,57,56;,
  4;58,57,65,66;,
  4;66,67,59,58;,
  4;52,59,87,60;,
  4;34,46,61,60;,
  4;62,61,46,35;,
  4;35,44,63,62;,
  4;64,63,44,85;,
  4;48,65,86,41;,
  4;66,65,48,40;,
  4;40,45,67,66;,
  4;60,67,45,34;;
 }
 MeshTextureCoords {
  68;
  0.365550;-0.089582;,
  0.326880;-0.091467;,
  0.327955;-0.131042;,
  0.366556;-0.118323;,
  0.375871;-0.107386;,
  0.417388;-0.084645;,
  0.367331;-0.126312;,
  0.330498;-0.120812;,
  0.329734;-0.079990;,
  0.388576;-0.082028;,
  0.184691;-0.088514;,
  0.285583;-0.080724;,
  0.240794;-0.106127;,
  0.329163;-0.137189;,
  0.333608;-0.049040;,
  0.327319;-0.038582;,
  0.366042;-0.057390;,
  0.387600;-0.072386;,
  0.245366;-0.115925;,
  0.215709;-0.112224;,
  0.326680;-0.062927;,
  0.365360;-0.079444;,
  0.283211;-0.041649;,
  0.282401;-0.056799;,
  0.263002;-0.065125;,
  0.282866;-0.091651;,
  0.305232;-0.059959;,
  0.305547;-0.091611;,
  0.306568;-0.131398;,
  0.307835;-0.140620;,
  0.282668;-0.122539;,
  0.308348;-0.080346;,
  0.307399;-0.056340;,
  0.305807;-0.032243;,
  0.309977;0.034027;,
  0.318641;0.061161;,
  0.311472;0.061161;,
  0.298913;0.034027;,
  0.254673;0.028495;,
  0.281567;-0.001923;,
  0.283062;0.034027;,
  0.240447;0.061161;,
  0.238952;0.061161;,
  0.259982;0.019005;,
  0.281567;0.162684;,
  0.238952;0.092393;,
  0.249146;0.124148;,
  0.283437;0.061161;,
  0.260565;0.057390;,
  0.279825;0.061161;,
  0.280538;0.034027;,
  0.265286;0.019412;,
  0.300365;0.119653;,
  0.282454;0.141062;,
  0.308977;0.061161;,
  0.309605;0.034027;,
  0.279911;0.092393;,
  0.308726;0.092393;,
  0.253473;0.107742;,
  0.314819;0.092393;,
  0.308855;0.076290;,
  0.317167;0.076290;,
  0.311472;0.076290;,
  0.283549;0.076290;,
  0.246941;0.094831;,
  0.238952;0.076290;,
  0.251003;0.076290;,
  0.279580;0.076290;;
 }
}
