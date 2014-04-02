<html>
  <head>
    <title>Jsp avarage!</title>
  </head>
  <body>
    <H2>Finding Average Grades</H2>
    <%
          double grades[] = {88, 98, 73, 56, 86, 64};
      double sum, average;
      
      sum = 0;
      
      for (int i = 0; i < grades.length; i++) {
          sum += grades[i];
      }
      
      average = sum / grades.length;
      
      out.println("<P>Average grade = " + average + "</P>");
    %>
       
  </body>
</html>
