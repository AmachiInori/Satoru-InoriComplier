# Satoru�ʷ�������

## �ʷ���Լ

Satoru�涨�����¼��ִʷ���Ԫ��

### ����������  

���ս���Ŷ�����ο�[DFA.md](DFA.md)

- ʮ�����з������� $\bold{digit10}^+$
- ʮ�����޷������� $\bold{digit10}^+(\bold{U|u})$  
- ʮ���Ƹ����� $\bold{digit10}^+.\bold{digit10}^+$
- ʮ����ָ��������$\bold{digit10}^+.\bold{digit10}^+(\bold{e|E})(\bold{+|-})?\bold{digit10}^+$
- �������з������� $\bold{0}\bold{X}\bold{digit2}^+$
- �������޷������� $\bold{0}\bold{X}\bold{digit2}^+(\bold{U|u})$
- ʮ�������з������� $\bold{0}\bold{X}\bold{digit16}^+$
- ʮ�������޷������� $\bold{0}\bold{X}\bold{digit16}^+(\bold{U|u})$

### ��ʶ��

- $\bold{idChar}(\bold{idChar} | \bold{digit10})^*$

### �ַ���������

- $\bold{"}(\bold{stringChar})^*\bold{"}$

### �ַ�������

- $\bold{'}(\bold{stringChar})^*\bold{'}$

### �����

- ���ɵ��ַ����ֵ������ $\bold{compChar}$
- ���Ե������֡������ظ�����Ҳ�ɽ����Ⱥŵ������ $\bold{repeatableChar}(\bold{[sameChar]})?|\bold{repeatableChar}(\bold{=})?$
- ���Ե������֡������ɽ����Ⱥŵ������ $\bold{doubleCompChar}(\bold{=})?$

## ����

- Satoru�ʷ���������**ʧ�䶪��**���ԣ����ִʷ�ʧ��֮�����һ������ʷ���Ԫ������һ���ַ������ʷ�������  
- �ָ���Ĭ�ϲ����⴦����һ���״̬ת���߶������зָ�����
- Satoru�ʷ�����ʹ���ƥ����ȥ������  