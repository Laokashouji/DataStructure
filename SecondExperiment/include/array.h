#include <cstdarg>
#include <cstdlib>
#define OK 1
#define ERROR -1
#define MAX_DIM 8 ///������������ά��

typedef int ElemType;
typedef int Status;


template <class ElemType>
class Array //��������˳��洢
{
private:
    ElemType *base;
    int dim;     //����ά��
    int *bounds; //�����ά�ĳ���
    int *constants; //����ά��ӳ���ַ

public:
    Status InitArray(int nDim, ...);     ///��ʼ������ pArr
    Status DestroyArray();               ///�������� pArr
    Status Locate(int nDim, va_list ap); ///��λ�±�ָ���Ԫ���������е�λ��
    Status Assign(ElemType *elm, ...);   ///���鸳ֵ
    Status Value(ElemType *elm, ...);    ///����ȡֵ
};



template <class ElemType>
Status Array<ElemType>::InitArray(int nDim, ...)
{
    if (nDim < 1 || nDim > MAX_DIM)
        return ERROR;

    ///��ʼ�� pArr ����ά������
    dim = nDim;

    ///��������ά���ַ
    bounds = (int *)malloc(nDim * sizeof(int));
    if (!bounds)
        return ERROR;

    int i = 0, nElemCount = 1;
    va_list ap;
    va_start(ap, nDim);

    /// i = nDim - 1, ʹ������
    for (i = nDim - 1; i >= 0; --i)
    {
        bounds[i] = va_arg(ap, int);
        if (bounds[i] < 0)
            return ERROR;

        nElemCount *= bounds[i];
    }
    va_end(ap);

    ///��ʼ��Ԫ�ػ�ַ
    base = (ElemType *)malloc(nElemCount * sizeof(ElemType));
    if (!base)
        return ERROR;

    ///��ʼ������ӳ������ַ
    constants = (int *)malloc(nDim * sizeof(int));

    ///����������ַ, ������
    constants[nDim - 1] = 1;
    for (i = nDim - 2; i >= 0; --i)
    {
        constants[i] = bounds[i + 1] * constants[i + 1];
    }

    return OK;
}

template <class ElemType>
Status Array<ElemType>::DestroyArray()
{
    if (base)
        free(base);

    if (bounds)
        free(bounds);

    if (constants)
        free(constants);

    return OK;
}

template <class ElemType>
Status Array<ElemType>::Locate(int nDim, va_list ap)
{
    int nPos = 0, ind = 0, i = 0;

    ///���������ַ
    for (i = dim - 1; i >= 0; --i)
    {
        ind = va_arg(ap, int);
        nPos += constants[i] * ind;
    }
    va_end(ap);

    return nPos;
}

template <class ElemType>
Status Array<ElemType>::Assign(ElemType *elm, ...)
{
    int nPos = 0;
    va_list ap;
    va_start(ap, elm);
    nPos = Locate(dim, ap);
    *(base + nPos) = *elm;

    return OK;
}

template <class ElemType>
Status Array<ElemType>:: Value(ElemType *elm, ...)
{
    int nPos = 0;
    va_list ap;
    va_start(ap, elm);
    nPos = Locate(dim, ap);
    *elm = *(base + nPos);
    return OK;
}

