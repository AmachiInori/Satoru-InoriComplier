# �ʷ�������

## �����ܹ�

## �ʷ���Լ

`token`�ǻ���
- `type` token���ͣ�ͨ��getTokenType()����
- ���캯����char���͵�tokentype

`numToken`������ Ҳ�ǻ���
- `exprValue`��ģʽƥ����ܵõ��������ַ���
- `numtype`���������ͣ�char
- ���캯�������洮����������

`intToken`������ final �˴���Ҫ����ֲ���Ż�
�������Ĺ�Լ��$((+|-)?digit^+U)$

`floatToken`������ ��Լ��
$((+|-)?digit^+.digit^+)|((+|-)?digit^+.digit^+(e|E)(+|-)?digit^+)$

Ĭ�ϵײ�ʵ��ʹ�ò����ʾ������������ʽ�ۼӣ���64λ�з�������(long long)����
`if (value > LLONG_MAX / 10.0)`�ж�����������ڹ��캯������expection�������̫ҵ����
�����������`getValueNum()`���ף�`int_cstexpe_overflow`��ʾ����쳣

`stringToken`�ַ����������࣬Ĭ�ϲ�Ҫ����

