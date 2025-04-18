/*********************************************************************************************/
/* A square response Matix for the experiment. Takes a binned pdf and applies the detector   */
/* to produce a new BinnedPhysDist. Inside is a vector of vectors, component fResponse[i][j] =    */
/* R_i_j = fraction of contents in bin j of original pdf -> bin i in the output pdf          */
/* the output bin contents are then x'_j = sum(R_i_j * x_j)                                  */
/* The systematic object is responsible for pdf renormalisation - not here                   */
/*********************************************************************************************/

#ifndef __OXSX_SPARSE_MATRIX__
#define __OXSX_SPARSE_MATRIX__
#include <armadillo>
class BinnedPhysDist;

class SparseMatrix
{
public:
   SparseMatrix() : fNRows(0), fNCols(0) {}
   SparseMatrix(size_t rows_, size_t cols_);
   std::vector<double> operator()(const std::vector<double> &input_) const;

   void SetComponent(size_t row_, size_t column_, double val_);
   double GetComponent(size_t row_, size_t column_) const;

   void SetComponents(const std::vector<long long unsigned int> &rowIndices_,
                      const std::vector<long long unsigned int> &colIndices_,
                      const std::vector<double> &values_);

   SparseMatrix operator*=(const SparseMatrix &other_);
   SparseMatrix operator*(const SparseMatrix &other_);
   size_t GetNRows() const { return fNRows; }
   size_t GetNCols() const { return fNCols; }
   void SetZeros();
   void SetToIdentity();

   void Print(const std::string &) const;
   void PrintDense(const std::string &) const;

private:
   arma::sp_mat fArmaMat;
   size_t fNRows;
   size_t fNCols;
};
#endif
