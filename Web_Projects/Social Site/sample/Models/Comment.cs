using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace sample.Models
{
    public class Comment
    {
        [Key]
        public int Id { get; set; }

        public int UserID { get; set; }
        public string Text { get; set; }
        public string Date { get; set; }
        public int BlogID { get; set; }
        public string AuthorName { get; set; }
    }
}