         X   W      "���������9Nԩ�A��֝��1�����            u@piece( SetCrossPlatformSettings )
#include <metal_stdlib>
using namespace metal;
@end
     X     B   �      #�    ����,n��w=|�0�X8�\�5            x�c``b�`�⒢�������C�j.N0K���2��T���s 
�+4�*4 ,��Zk. �6�     �     -   �     %_   ����y3�m�M?z�Ժ3�����T�               �   �   !
#define mul( x, y ) ((x) * (y))
     �     "   �     %`   ����iM�����	��`������f�               �   �   #define INLINE inline
     �     .       %�   ����l,�$���n�k����K�            x�c``�� �Z\�)�i�y�
��%a���ř%��y�^z\� �hb         X  h     &A   ����h˅��qx ���i�pZ����            x�c``�� �)�)�i�y�
��A�����9�>�e�9
%�:
�`�"��2���M��DX!����Xb�T��	T1�^� �'"�    o       y     &O   �����C�c���v���2J�/               �   �   #define lerp mix
    �     (  �     )-   ����)l&{�7�; ���R�oy�               �   �   #define finalDrawId drawId

    �     q  #     )X   �������mF��=Ť��(?���            x�c``�� �}�)�i�y�
��A�����9��EE��F.>�e�9
%�:
�`�"��2�D��g
P8'?EA�B� ]uZN~b��P��&PoqF~Q�\?H,b	� M. |�0�    %     v       )]   ������._��O�8��y9�l9�            x�c``����$���Щ������������[���XT�Xi��Z����P�Z��P�(�Q(-�QH�{� �s�S4A*� 
4
�r�K�4�4�ڊ3�J4�ZAb9�!fhr I/.r    �     @  g   	  )�   	����%	Ҵ7zg�N"�hѩ4��i            x�c``x� ���)�i�y�
~��~!�A�>�!��~�A�n�\8�C݀�
��i9�%��\ ��    �     F  �   
  )�   
����3���G�m|�0��u            x�c``Jb cw�Դ̼T� �x�Ҵ��"�Ԓ�C�$0OG!3��'?9�$3?OA*��$�� �E�    !     �  �   	  2�   	�����7&�o=%PV7.�����            x�uPK
�0u��pa��nEP��B?7H*��J%��7�
�|�V��2�޼7	 �����"c�2�F	�=�#����Ż�<�Z�v�H`F��6�6�%Qd�^�'�?�z�^�5'�1e���b�B`TL.g��~͎�H�BQ�l�R<_̢Bu�'����*܆i�r�kJ�j��?{��OlLY�#�M�WD�Rƫ�8W���?��Aφ"��v(��_ls4C��"���u���%Mq��Z�         5  (     2�   �����a3Ջ�
���!���`���w            x�c``�� �\�)�i�y�
I�ii�En�%�P��BfJ��&���r pv    G     o  �     2�   ������v��U2@��f�����_#�            x�c``^� ���)�i�y�
��A�����9��EE��F.�E�)
%�:
�`�"��2���
Q��	�ԃ�i��)-��/*�PH�R�����4/35��h*��\ s�-    �     �  �     2�   ������*c޽暒 ~˩��x�            x�c``^�������Ы������������[���XT�Xi��^����P�Z��P/�Q(-�QHI{� �S D��&H�D��������.M�t�ə�y%F@����:j3��T���Z�Z��a���(d�L�򢁜X. ^FB>    L     A  .     2�      �fY%��s g�o�`����            x�c``�e cO�Դ̼T?�xO�נ �O��� W7�.����n@y��贜Ē�X. k6    �     8  ,     2�   ����U�u�J
����9��)�            x�c``8� ���)�i�y�
I��9)n9��%��
E��: �L)h*��� ׵
    �     8  u     3
      W�𝪒S&��0 ���F�            x�c``8� ���)�i�y�
I��9)n9��%��
E��: �L)h*��� ׵
    �     t        3O   ����LU2z������J-_)�            x�c``�� ���)�i�y�
��A�����9��EE��ΥI�>�e�9
%�:
�`�"��2�D�
��pN~��&H�D�BaZN~b��P��&P[qF~Q�\+H,b>�M. bH0y    q     ?  ]     3_   ����,�%oQ.e}N��2yt�ig�            x�c``�e c�X�Դ̼T���<c�D�$�dM��P1M.���
TՉ� �� ���    �     �  b     4   ������X%^���7�~'�L�E�            x����j�@E�����җB���v#B�H�BQ$l��.��$k���~��X(}���s���ݎ��=>ո6�b۪/�8�* ��� "����+����sQz���b�����ڳ�İ�b�ۚRH2�9_�����0�]jF�,T�6K����g#��x")�7���z���q�q�ӭq�����g���:�]Y�iz�jHҡ*'R�|��C�8Ը��{���~�����NLHx�    �     ,  �     4%   ����U���ap5�1%�N�W ���               �   �    #define ogre_float4x3 float3x4

    �     �  E     4H   ����#G��g���&M��;'L            x�c``�� �Z�)�i�y�
i9��%N�%�!��y%�
���%��6�y%v@>P�mf��Ӗ���[���X��g�*���S4%�� ?'�$ձ�B*��P\�TR�$Z!�	@"�'�I!���� ��HB    K     -  h     4I   ����&�4���P{�L ��ɾ��            x�c``�� ���)�i�y�
)��ɉE)0:>�(1=75�DC� 4�n    x      
w     4Z   ����ы�S2}��Q-d�>�            x�u��J�0���ܽ����(�"e�/%mf�@v�����춅k``��!�?�'o�v
�)|qE��Ϙ��Sk��� �!�����ƻ�Jp�RU0�i�{�5�����m���}q�6[�P��)[����4��_���A�.]�^��2�N���iATg�޻"tEe�åB����'PB�x�v�M����k�o����T���>��h�<<��Fț5g�VL�nŴ�,9�i�Y�H�O۩ׅ҉���w¤E���    	�     �  
�     4[   ����u�ֵ��ʃE�|�q����M�            x�c``�� ���y9�y�
i9��%��
%��`�DȤ�D!WA���K�RKJ����5r�b�**�t�,C8��Rд���b``��ׁ����PNIM٘�V�R�X���X��W\��������0=S4A��20����ҟ�WPZ�� 5��A0�
Lq~iI@q|r~N~i����q �MNN    
E       �     4`   ������/�?g8/[y2ƴ��>	            x�c``T` c�+����E%
�ũ)
i�E
E��)
��E�%��y�z
�%��
�y
�y%@���죠��������2��%�9\�)�i�y�
E`q#���E�E�%��lB��b9�M�h6q |�G�    
�     .  �     5    �����-Gٕ�X(W�;H51`T            x�c``1a cU�Դ̼T�̼����Ԣ��
� ���D�� �a    
�       �     5   �������h����3�H��3s'[�@              4  Y        
�     $  �     7?   �������x�c"�p��p\:�KYH              �  �   #define wshort3 ushort3
    "     �  R     7Y   �����)�@Kr�V���E��=            x�c`��� �U�)�i�y�
��A�����>�A�A��.��>
ŉ�9�E~���
�
:0>�8.#p���b`�~�P���ru�PHIM�	�,H�Q(K,�LL�I�U�Q����WPC�G5�ӏR�����;�����P�*�C������B- `�{    �     8  �     7�   ����*2P%�*���;��n�4��            x�c`��� ��)�i�y�
��A��!�%�E��.�i9��%&
%P��� ��         /  �      7�    �����7���Y��x�Kkw��              d  d   ##define OGRE_ARRAY_START( type ) {
    1       l   !  7�   !�������jX���+|���B�f)z��              +  d        =     S  �   "  7�   "��������)�9��4�bmYat�            x�c``�d c!�Դ̼T��̼�R �������`��%E��%�E�)N�ii�En�%�
I`��BfJ��&���rq l�D    �     �  [   #  8   #�����XǷ,������r���I��w            x�c``�� ���y9�y�
i9��%��
%��`�L�D!WA�����(���(�RC!7� V���J�2����,Mk�Z.��জ�����=�5�'?1��EC�$�BG!��LG!'?EA��+JML�P(-��/*��UЄ�sq qD7#    #     �  �   $  9   $����W�k:x�w&���ߴ���	            x�c``�c``]���p�ӡ�(� ���RCA1#'�8>3��$1/95%��$�(5_A���S9%5-3/U!3/�8>�(��3EA#)�8��ZA[��3��!5�8�F<:��K1��8Ņ(��R���[�g�>\I�3�
JK� ^BVJ�Ѝ;����a�KK�:�2S��J<�RR+ bz�9�a��\ P��