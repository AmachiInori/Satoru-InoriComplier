`token`�ǻ���
- `type` token���ͣ�ͨ��getTokenType()����
- ���캯����char���͵�tokentype

`numToken`������ Ҳ�ǻ���
- `exprValue`��ģʽƥ����ܵõ��������ַ���
- `numtype`���������ͣ�char
- ���캯�������洮����������

`intToken`������ final
Ĭ�ϵײ�ʵ��ʹ�ò����ʾ������������ʽ�ۼ�
`if (value > LLONG_MAX / 10.0)`�ж�����������ڹ��캯������expection�������̫ҵ����
�����������`getValueNum()`���ף�`int_cstexpe_overflow`��ʾ����쳣