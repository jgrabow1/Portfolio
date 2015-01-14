
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace sample.Models
{
    public enum Totema { Monkey, Squirrel };

    public class Person
    {
        [Key]
        public int Id { get; set; }

        public Totema Totema { get; set; }
        [Required]
        public string First { get; set; }
        [Required]
        public string Last { get; set; }
        [Required]
        [DataType(DataType.EmailAddress)]
        public string Email { get; set; }
        [Required]
        public string Username { get; set; }
        [Required]
        [DataType(DataType.Password)]
        public string Password { get; set; }
        public int Str { get; set; }
        public int Vit { get; set; }
        public int Int { get; set; }
        public string image { get; set; }
    }

}