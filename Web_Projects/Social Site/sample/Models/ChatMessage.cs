using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace sample.Models
{
    public class ChatMessage
    {
        [Key]
        public int Id { get; set; }

        public int AuthorId { get; set; }
        public string AuthorUsername { get; set; }
        public int InstanceId { get; set; }
        public string Text { get; set; }
        public string Date { get; set; }
    }
}