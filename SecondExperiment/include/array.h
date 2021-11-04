#include <cstdarg>
#include <cstdlib>
#define OK 1
#define ERROR -1
#define MAX_DIM 8 ///允许的最大数组维数

typedef int ElemType;
typedef int Status;


template <class ElemType>
class Array //按列优先顺序存储
{
private:
    ElemType *base;
    int dim;     //数组维数
    int *bounds; //数组各维的长度
    int *constants; //数组维界映像基址

public:
    Status InitArray(int nDim, ...);     ///初始化数组 pArr
    Status DestroyArray();               ///销毁数组 pArr
    Status Locate(int nDim, va_list ap); ///定位下标指向的元素在数组中的位置
    Status Assign(ElemType *elm, ...);   ///数组赋值
    Status Value(ElemType *elm, ...);    ///数组取值
};



template <class ElemType>
Status Array<ElemType>::InitArray(int nDim, ...)
{
    if (nDim < 1 || nDim > MAX_DIM)
        return ERROR;

    ///初始化 pArr 数组维数属性
    dim = nDim;

    ///构造数组维界基址
    bounds = (int *)malloc(nDim * sizeof(int));
    if (!bounds)
        return ERROR;

    int i = 0, nElemCount = 1;
    va_list ap;
    va_start(ap, nDim);

    /// i = nDim - 1, 使列优先
    for (i = nDim - 1; i >= 0; --i)
    {
        bounds[i] = va_arg(ap, int);
        if (bounds[i] < 0)
            return ERROR;

        nElemCount *= bounds[i];
    }
    va_end(ap);

    ///初始化元素基址
    base = (ElemType *)malloc(nElemCount * sizeof(ElemType));
    if (!base)
        return ERROR;

    ///初始化函数映像常数基址
    constants = (int *)malloc(nDim * sizeof(int));

    ///递推求常量基址, 列优先
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

    ///列优先求地址
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

