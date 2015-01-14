using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace sample.Models
{
    public class Blog
    {
        [Key]
        public int Id { get; set; }

        public int HPage { get; set; }
        public int AuthorID { get; set; }
        public string AuthorName { get; set; }
        public string Text { get; set; }
        public string Date { get; set; }
    }
}