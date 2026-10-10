# Problem 077 - 这是道工程题

**ACMOJ Problem ID**: 1410

## Table of Contents

- [Problem 077 - 这是道工程题](#problem-077-这是道工程题)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [OJ Git Repository Compilation Process](#oj-git-repository-compilation-process)
    - [Git Configuration Requirements](#git-configuration-requirements)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

This problem tests algorithmic problem-solving skills.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **1410. 这是道工程题** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/077/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

助教发现上次机考写工程题的同学好像不是很多，为了鼓励大家尝试工程题，因此助教决定出一出大家已经学会的指针和类，相信大家都已经得心应手了吧。

本题描述如下：

你需要实现一个类：`CrossArray`。

`CrossArray`类要实现为以`int`为元素的二维交错数组的功能。二维交错数组由若干个数组并联在一起，但每个数组彼此间长度不一定相同。

- 注意：**本题禁止使用任何库。**

而更具体地，你需要实现的每个类的对外接口如下：

#### `CrossArray`类：

- `CrossArray(int lines):` 构造函数，`lines`代表最多有多少个数组并联在一起，注意，此时二维交错数组中的每个一维数组都视为`nullptr`。
- `CrossArray(const CrossArray & o):` 拷贝构造函数，用`o`中的信息构造一个新的`CrossArray`类，新的类二维数组的每一个元素都应当与`o`的对应元素相同。

- `bool InsertArrays(const int * Input, int size):` 插入数组函数，插入的数组大小为`size`，第`i`个插入的数组记它在二维数组里的下标为`i-1`，相当于用数组`Input`里的元素填充二维数组里的一维数组。若插入`Input`后总计存在的一维数组的数量超过了构造时的上限，则返回`false`，且该次插入不会发生；反之，返回`true`。

- `void AppendArrays(const int * Input,int Line,int size):` 增长数组函数，`Line`对应一维数组的下标，在该一维数组后增加`Input`数组，`Input`数组大小为`size`。保证该函数只会在已经`Insert`的数组后面`Append`并且保证`Line`合法。
- `CrossArray & WhichGreater(CrossArray & o):` 比较大小函数，比较当前类的所有元素个数与`o`中的所有元素个数谁更大，返回更大的那个`CrossArray`；若二者相同元素个数，返回当前类。
- `bool IsSame(const CrossArray & o):` 是否相同函数，比较当前类的空间与`o`是否属于同一块空间，若是，返回`true`；反之返回`false`。 

- `void DoubleCrossLength():` 翻倍空间函数，将`CrossArray`中的数组并联上限翻倍，保持原有的一维数组元素与下标不变，新增的一维数组均视为`nullptr`。

- `const int * AtArray(int i):` 取数组函数，返回下标为`i`的数组的首指针。若该数组为`nullptr`，则返回`nullptr`。保证`i`合法。

- `int & At(int i , int j):` 取值函数，返回下标为`i`数组的第`j`个元素。`i,j`均为`0-base`，保证`i,j`合法。

- 以及`CrossArray`类的析构函数。

### Input Format

本次你实现的类将作为**hpp**被测试。请将如下部分的代码复制后，完成题目要求，并且注意检查内存泄漏。我们将调用如上提到的函数接口。你可以自己实现额外的函数以方便完成题目。

```
namespace sjtu {
    class CrossArray{
    private:
    public:
        explicit CrossArray(int lines);

        CrossArray(const CrossArray & o);

        CrossArray & WhichGreater(CrossArray & o);

        bool IsSame(const CrossArray & o);

        bool InsertArrays(const int * Input, int size);

        void AppendArrays(const int * Input,int Line,int size);

        void DoubleCrossLength();

        const int * AtArray(int i);

        int & At(int i , int j);

        ~CrossArray();

    };
}
```

##

### Output Format

#### 得分分布：

1. 若你完成了`CrossArray`类的`构造函数`与`析构函数`与`InsertArrays`函数，你将得到$30\\%$的分数。
2. 在此基础上，若你额外完成了`At`函数，你将额外得到$10\\%$的分数。“额外”的含义为，在评测`At`的函数时，我们会用到先前的函数。
3. 例如，你没有完成`InsertArrays`函数，而只完成了`At`函数，那么你将不会得到`At`函数的额外分数。如下的函数测评则会依次递进，你只有完成先前的函数，才有可能能拿到额外的分数。
4. `CrossArray`的`拷贝构造`对应额外$15\\%$的分数。
5. `Append`函数对应额外$15\\%$的分数。
6. `Greater`和`IsSame`一同对应额外$10\\%$的分数。
7. `AtArrays`对应额外$5\\%$的分数。
8. `DoubleCrossLength`对应额外$15\\%$的分数。
9. 另外，在机考时，虽然我们不做要求，但还是希望同学们能尽可能保持自身良好的工程习惯。
10. **由于c++的语法，在类中只声明函数而没有实现该函数将会引发CE。**

### Samples

#### Sample 1

### Data Constraints

对于`CrossArray`类，保证数组并联的上限小于等于1000。

对于`CrossArray`类里的每一个一维数组，长度保证小于等于10000。

## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 1000 ms
- **Memory Limit (per test case)**: 256 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/077/data_test/`.

## Submission Requirements

### OJ Git Repository Compilation Process

For Git compilation, we will first clone the repository using a command similar to:
```bash
git clone <repo_url> . --depth 1 --recurse-submodules --shallow-submodules --no-local
```

Then we check if there is a `CMakeLists.txt` file. If it exists, we run (if not, a warning message will be displayed):
```bash
cmake .
```

Finally, we check if there is any of `GNUmakefile`/`makefile`/`Makefile` (if cmake was run previously, this will be the generated Makefile). If it exists, we run (if not, a warning message will be displayed):
```bash
make
```

After this process is complete, we will use the `code` file in the project root directory as the compilation result.

A `CMakeLists.txt` file is provided in the project. You can use or modify it as needed. The local environment has gcc-13 and g++-13 available.

### Git Configuration Requirements

**IMPORTANT**: You must create a `.gitignore` file in your project root directory to avoid OJ evaluation conflicts.

The `.gitignore` file should include at least the following entries:

```gitignore
CMakeFiles/
CMakeCache.txt
```

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The compiled executable file name must be `code`
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
