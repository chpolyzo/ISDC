import math
from math import sqrt
import numbers

def zeroes(height, width):
        """
        Creates a matrix of zeroes.
        """
        g = [[0.0 for _ in range(width)] for __ in range(height)]
        return Matrix(g)

def identity(n):
        """
        Creates a n x n identity matrix.
        """
        I = zeroes(n, n)
        for i in range(n):
            I.g[i][i] = 1.0
        return I

class Matrix(object):

    # Constructor
    def __init__(self, grid):
        self.g = grid
        self.h = len(grid)
        self.w = len(grid[0])
        
    def __str__(self):
        return f"Matrix({self.g})"
        
    def is_square(self):
        return self.h == self.w
        
        
        
    def determinant(self):
        """
        Calculates the determinant of a 1x1 or 2x2 matrix.
        """
        if not self.is_square():
            raise(ValueError, "Cannot calculate determinant of non-square matrix.")
        if self.h > 2:
            raise(NotImplementedError, "Calculating determinant not implemented for matrices largerer than 2x2.")
            
        try:
            # calculate the determinant of the original 2x2 matrix
            det = (self.g[0][0] * self.g[1][1] - self.g[1][0] * self.g[0][1])
        except:
            # calculate the determinant of the original 1x1 matrix
            det = self.g[0][0]
        return det
    
    def trace(self):
        """
        Calculates the trace of a matrix (sum of diagonal entries).
        """
        if not self.is_square():
            raise(ValueError, "Cannot calculate the trace of a non-square matrix.")
        
        tr = sum([self.g[i][j] for i in range(self.h) for j in range(self.w) if i == j])
        
        return tr
    
    
    def inverse(self):
        """
        Calculates the inverse of a 1x1 or 2x2 Matrix.
        """
        if not self.is_square():
            raise(ValueError, "Non-square Matrix does not have an inverse.")
        if self.h > 2:
            raise(NotImplementedError, "inversion not implemented for matrices larger than 2x2.")
            
        try:
            # calculate the adjoint of the original 2x2 matrix
            adjoint = 1 / (self.g[0][0] * self.g[1][1] - self.g[0][1] * self.g[1][0])
            # create the swaped grid
            swap = [[self.g[1][1], -self.g[0][1]],[-self.g[1][0], self.g[0][0]]]
            # create the inverse list
            inv = [adjoint * swap[i][j] for i in range(len(swap)) for j in range(len(swap[0]))]
            # create matrix from grid
            mtx = Matrix([[inv[0], inv[1]],[inv[2], inv[3]]])
            
        except:
            # calculate inverse of an 1x1 matrix
            inv = [1 / self.g[0][0]]
            # create the matrix from the grid
            mtx = Matrix([inv])
              
        return mtx
    
    def T(self):
        """
        Returns a transposed copy of this Matrix.
        """
        try:
            # create the transposed list
            trs_ls = [self.g[j][i] for i in range(len(self.g[0])) for j in range(len(self.g))]
            # handle 2x2 matrix
            trs_mtx = Matrix([[trs_ls[0], trs_ls[1]],[trs_ls[2], trs_ls[3]]])
        except:
            # handle 1x1 matrix
            trs_mtx = Matrix([self.g[0]])
            
        
        return trs_mtx
    
    ##############################
    # Begin Operator Overloading #
    ##############################
    def __getitem__(self,idx):
        """
        Defines the behavior of using square brackets [] on instances
        of this class.

        Example:

        > my_matrix = Matrix([ [1, 2], [3, 4] ])
        > my_matrix[0]
          [1, 2]

        > my_matrix[0][0]
          1
        """
        return self.g[idx]
    
    def __add__(self,other):
        """
        Defines the behavior of the + operator
        """
        if self.h != other.h or self.w != other.w:
            raise(ValueError, "Matrices can only be added if the dimensions are the same") 

        try:
            # create the expected sum as a lis for 2x2 matrix
            add_ls = [self.g[i][j] + other.g[i][j] for i in range(len(self.g)) for j in range(len(self.g[0]))]
            # handle 2x2 matrix
            mtx_add = Matrix([[add_ls[0], add_ls[1]],[add_ls[2], add_ls[3]]])
        except:
            # handle 1x1 matrix
            mtx_add = Matrix([self.g[0]])
            
        return mtx_add
    
    def __neg__(self):
        """
        Defines the behavior of - operator (NOT subtraction)
        Example:
        > my_matrix = Matrix([ [1, 2], [3, 4] ])
        > negative  = -my_matrix
        > print(negative)
          -1.0  -2.0
          -3.0  -4.0
        """

        try:
            # create the expected negative numbers in a list for a 2x2 matrix
            neg_ls = [float(-self.g[i][j]) for i in range(len(self.g)) for j in range(len(self.g[0]))]
            # handle 2x2 matrix
            mtx_neg = Matrix([[neg_ls[0], neg_ls[1]],[neg_ls[2], neg_ls[3]]])
        except:
            # handle 1x1 matrix
            mtx_neg = -self.g[0][0]
            
        return mtx_neg

    def __sub__(self,other):
        """
        Defines the behavior of the + operator
        """
        if self.h != other.h or self.w != other.w:
            raise(ValueError, "Matrices can only be added if the dimensions are the same") 

        try:
            # create the expected sum as a lis for 2x2 matrix
            sub_ls = [self.g[i][j] - other.g[i][j] for i in range(len(self.g)) for j in range(len(self.g[0]))]
            # handle 2x2 matrix
            mtx_sub = Matrix([[sub_ls[0], sub_ls[1]],[sub_ls[2], sub_ls[3]]])
        except:
            # handle 1x1 matrix
            mtx_sub = Matrix([self.g[0]])
            
        return mtx_sub
    
    def dot(self_vector, other_vector):
        """
        Defines the behavior of vector multiplication 
    
        """
        dot_ls = sum( [self_vector[i]*other_vector[i] for i in range(len(other_vector))] )
        
        return dot_ls
    
    def __mul__(self,other):
        """
        Defines the behavior of * operator (matrix multiplication)
        """
        result_mul = [[sum(self.g[i][k] * other.g[k][j] for k in range(other.h)) \
                       for j in range(other.w)] for i in range(self.h)]
        
        if self.w == other.h:
            return Matrix(result_mul)
    
    def __rmul__(self, other):
        """
        Called when the thing on the left of the * is not a matrix.
        Example:
        > identity = Matrix([ [1,0], [0,1] ])
        > doubled  = 2 * identity
        > print(doubled)
          2.0  0.0
          0.0  2.0
        """
        if isinstance(other, numbers.Number):
            pass
        
            rmul_ls = [other * self[i][j] for i in range(len(self.g)) for j in range (len(self.g[0]))]
        try:
            mtx_rmul = Matrix([[rmul_ls[0], rmul_ls[1]],[rmul_ls[2], rmul_ls[3]]])
            
        except:
            mtx_rmul = other * self.g[0][0]
            
        
        return mtx_rmul


    
    def __repr__(self):
        """
        Defines the behavior of calling print on an instance of this class.
        """
        s = ""
        for row in self.g:
            s += " ".join(["{} ".format(x) for x in row])
            s += "\n"
        return s