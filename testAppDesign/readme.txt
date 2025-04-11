Design a test taking website type service where user can register/login,


give the test and can see their past test score and rankings.

- Test can be of multiple types and questions in test can be of multiple type (mcq, yes/no, fill in the blanks, multiple correct options) with 
the questions can being both image and direct string.

- Questions should be unique to every user in a particular test and in case of user being dropped from the test (bad internet or anything) 
he can resume the test from where he left provided he came before his test timer was off.



user:
name
id password



userManager:
userid , user
add user


test:
questions
total score
test score





question:
Answer Type Single_choice_mcq , YES/NO , FILL_IN_THE_BLANKS , multiple_Choice_MCQ
question Type: string , image
Options?
score
answer



testManager:
user , unordered_map<user , vector<int>> user->all test
testId, vector<Students>


ConductTest
view score







